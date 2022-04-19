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
        return gl_Vertex;
    }

    virtual bool fragmentShader(Vec3f barycentric_coords, TGAColor& color) {
        Vec4f shadowbuffer_p = uniform_shadow_MVP * embed<4>((varying_tri * barycentric_coords), 1.0f);
        shadowbuffer_p = shadowbuffer_p / shadowbuffer_p[3];                           // ndc
        int frag_index = int(shadowbuffer_p[0]) + int(shadowbuffer_p[1]) * SCR_WIDTH;  // frag在shadowbuffer中的下标

        // 若 shadow_buffer 已存储深度 等于 当前 frag 在 shadow_buffer 的深度，才能点亮
        float old_depth = shadow_buffer[frag_index];
        float frag_depth = shadowbuffer_p[2];
        bool isLit = old_depth - frag_depth < 43.34f;  // TODO:为什么已有的depth > frag_depth 才能点亮，反过来不行？用绝对值也不行？

        Vec2f uv = varying_uv * barycentric_coords;

        TGAColor ambientColor(10, 10, 10);

        Vec3f normal = proj<3>(uniform_MVPIT * embed<4>(model->normal(uv), 0.0f)).normalize();
        Vec3f light = proj<3>(uniform_MVP * embed<4>(light_dir)).normalize();
        float diff = std::max(0.0f, normal * light);
        TGAColor diffuseColor = model->diffuse(uv);

        Vec3f reflectLight = (normal * (normal * light * 2.0f) - light).normalize();
        float spec = pow(std::max(reflectLight.z, 0.0f), model->specular(uv));

        // for (size_t i = 0; i < 3; ++i) {
        // color[i] = ambientColor[i] + diffuseColor[i] * (0.6f * spec + 1.2f * diff) * (isLit ? 1.0f : 0.5f);

        // }

        color = TGAColor(255, 255, 255) * ((normal * light) * (isLit ? 1.0f : 0.5f));
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
    // float* shadow_buffer = new float[SCR_WIDTH * SCR_HEIGHT];
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
    // float* z_buffer = new float[SCR_WIDTH * SCR_HEIGHT];
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
        frame.write_tga_file("7frame.tga");
    }

    {  // dump z-buffer (debugging purposes only)
        TGAImage zbimage(SCR_WIDTH, SCR_HEIGHT, TGAImage::GRAYSCALE);
        for (size_t i = 0; i < SCR_WIDTH; ++i) {
            for (size_t j = 0; j < SCR_HEIGHT; ++j) {
                zbimage.set(i, j, TGAColor(z_buffer[i + j * SCR_WIDTH]));
            }
        }
        zbimage.flip_vertically();  // i want to have the origin at the left bottom corner of the image
        zbimage.write_tga_file("7z_buffer.tga");
    }

    delete model;
    delete[] z_buffer;
    delete[] shadow_buffer;
    return 0;
}
