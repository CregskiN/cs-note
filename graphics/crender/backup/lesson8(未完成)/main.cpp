#include <vector>

#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
#include "our_gl.h"

Vec3f light_dir = Vec3f(1, 1, 0);
Model* model = NULL;

float* shadow_buffer = new float[SCR_WIDTH * SCR_HEIGHT];
float* z_buffer = new float[SCR_WIDTH * SCR_HEIGHT];

struct {
    Vec3f eye = Vec3f(1, 1, 4);
    Vec3f center = Vec3f(0, 0, 0);
    Vec3f up = Vec3f(0, 1, 0);
} Camera;

/*
    Gouraud shading：插值计算三角形内颜色，shading
    Phong shading：插值计算三角形内法线，再计算颜色 shading
 */

// Phong-like shading
struct Shader : public IShader {
    mat<4, 4, float> uniform_MVP;
    mat<4, 4, float> uniform_MVPIT;
    mat<4, 4, float> uniform_shadow_MVP;  // 将当前 screen_coords 转换为 shadow_buffer 中的 screen_coords
    mat<2, 3, float> varying_uv;
    mat<3, 3, float> varying_tri;  // vertex position (screen_coords)

    virtual Vec4f vertexShader(int iface, int nthvert) {
        varying_uv.set_col(nthvert, model->uv(iface, nthvert));
        Vec4f gl_Vertex = Viewport * uniform_MVP * embed<4>(model->vert(iface, nthvert));
        varying_tri.set_col(nthvert, proj<3>(gl_Vertex / gl_Vertex[3]));
        return gl_Vertex;  // not ndc
    }

    virtual bool fragmentShader(Vec3f barycentric_coords, TGAColor& color) {
        TGAColor ambientColor(125, 125, 125);

        color = ambientColor;

        return false;
    }
};

struct DepthShader : public IShader {
    mat<3, 3, float> varying_tri;

    DepthShader() : varying_tri() {}

    virtual Vec4f vertexShader(int iface, int nthvert) {
        Vec4f gl_Vertex = embed<4>(model->vert(iface, nthvert));    // read the vertex from .obj file
        gl_Vertex = Viewport * Projection * ModelView * gl_Vertex;  // transform it to screen coordinates
        varying_tri.set_col(nthvert, proj<3>(gl_Vertex / gl_Vertex[3]));
        return gl_Vertex;
    }

    virtual bool fragmentShader(Vec3f bar, TGAColor& color) {
        Vec3f p = varying_tri * bar;
        color = TGAColor(255, 255, 255) * (p.z / SCR_DEPTH);
        return false;
    }
};

int main(int argc, char** argv) {
    // model = new Model("../objs/african_head/african_head.obj");
    model = new Model("../objs/diablo3_pose/diablo3_pose.obj");

    // 1. 计算阴影深度

    {
        for (size_t i = 0; i < SCR_WIDTH * SCR_HEIGHT; ++i) {
            shadow_buffer[i] = -std::numeric_limits<float>::max();
        }
        TGAImage depth(SCR_WIDTH, SCR_HEIGHT, TGAImage::RGB);
        lookAt(light_dir, Camera.center, Camera.up);  // 光源位置，与相机看向同一个点，与相机共用一个上向量
        viewport(SCR_WIDTH / 8, SCR_HEIGHT / 8, SCR_WIDTH * 3 / 4, SCR_HEIGHT * 3 / 4);
        projection(0);  // 计算阴影深度，无需做透视扭曲

        DepthShader depthshader;
        Vec4f screen_coords[3];
        for (int i = 0; i < model->nfaces(); i++) {
            for (int j = 0; j < 3; j++) {
                screen_coords[j] = depthshader.vertexShader(i, j);
            }
            triangle(screen_coords, depthshader, depth, shadow_buffer);
        }
        depth.flip_vertically();
        depth.write_tga_file("7shadow_buffer.tga");
    }

    mat<4, 4, float> shadow_MVPV = Viewport * Projection * ModelView;  // 暂存 shadow MVP

    // 2. 绘制
    {
        for (size_t i = 0; i < SCR_WIDTH * SCR_HEIGHT; ++i) {
            z_buffer[i] = -std::numeric_limits<float>::max();
        }
        TGAImage frame(SCR_WIDTH, SCR_HEIGHT, TGAImage::RGB);
        lookAt(Camera.eye, Camera.center, Camera.up);
        viewport(SCR_WIDTH / 8, SCR_HEIGHT / 8, SCR_WIDTH * 3 / 4, SCR_HEIGHT * 3 / 4);
        projection(-1.f / (Camera.eye - Camera.center).norm());

        Shader shader;
        shader.uniform_MVP = Projection * ModelView;
        shader.uniform_MVPIT = (Projection * ModelView).invert_transpose();
        shader.uniform_shadow_MVP = shadow_MVPV * (Viewport * Projection * ModelView).invert();  // 将当前 screen_coords 转换为 shadow_buffer 中的 screen_coords
        Vec4f screen_coords[3];
        for (int i = 0; i < model->nfaces(); i++) {
            for (int j = 0; j < 3; j++) {
                screen_coords[j] = shader.vertexShader(i, j);
            }
            triangle(screen_coords, shader, frame, z_buffer);
        }

        frame.flip_vertically();
        frame.write_tga_file("8frame.tga");
    }

    {  // dump z-buffer (debugging purposes only)
        TGAImage zbimage(SCR_WIDTH, SCR_HEIGHT, TGAImage::GRAYSCALE);
        for (size_t i = 0; i < SCR_WIDTH; ++i) {
            for (size_t j = 0; j < SCR_HEIGHT; ++j) {
                zbimage.set(i, j, TGAColor(z_buffer[i + j * SCR_WIDTH]));
            }
        }
        zbimage.flip_vertically();  // i want to have the origin at the left bottom corner of the image
        zbimage.write_tga_file("8z_buffer.tga");
    }

    delete model;
    delete[] z_buffer;
    delete[] shadow_buffer;
    return 0;
}
