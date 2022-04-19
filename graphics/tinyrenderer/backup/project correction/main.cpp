#include <vector>

#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
#include "our_gl.h"

Vec3f light_dir = Vec3f(1, 1, 0);
Model* model = NULL;

float* z_buffer = new float[SCR_WIDTH * SCR_HEIGHT];



/*
    Gouraud shading：插值计算三角形内颜色，shading
    Phong shading：插值计算三角形内法线，再计算颜色 shading
 */

// Phong-like shading
struct Shader : public IShader {
    mat<2, 3, float> varying_uv;
    mat<4, 3, float> varying_clipped_coords;  // 4D列向量 * 3个

    virtual Vec4f vertexShader(int iface, int nthvert) {
        varying_uv.set_col(nthvert, model->uv(iface, nthvert));
        Vec4f gl_Vertex = Projection * ModelView * embed<4>(model->vert(iface, nthvert), 1.0f);
        varying_clipped_coords.set_col(nthvert, gl_Vertex);

        return gl_Vertex;
    }

    virtual bool fragmentShader(Vec3f barycentric_coords, TGAColor& color) {
        Vec2f uv = varying_uv * barycentric_coords;
        color = model->diffuse(uv);
        return false;
    }
};

int main(int argc, char** argv) {
    // model = new Model("../objs/african_head/african_head.obj");

    // 2. 绘制
    TGAImage frame(SCR_WIDTH, SCR_HEIGHT, TGAImage::RGB);
    {
        model = new Model("../objs/floor.obj");
        for (size_t i = 0; i < SCR_WIDTH * SCR_HEIGHT; ++i) {
            z_buffer[i] = -std::numeric_limits<float>::max();
        }

        lookAt(Camera.eye, Camera.center, Camera.up);
        viewport(SCR_WIDTH / 8, SCR_HEIGHT / 8, SCR_WIDTH * 3 / 4, SCR_HEIGHT * 3 / 4);
        projection(-1.f / (Camera.eye - Camera.center).norm());

        Shader shader;

        for (int i = 0; i < model->nfaces(); i++) {
            for (int j = 0; j < 3; j++) {
                shader.vertexShader(i, j);
            }
            triangle(shader.varying_clipped_coords, shader, frame, z_buffer);
        }

        delete model;
    }

    // {
    //     model = new Model("../objs/african_head/african_head.obj");
    //     for (size_t i = 0; i < SCR_WIDTH * SCR_HEIGHT; ++i) {
    //         z_buffer[i] = -std::numeric_limits<float>::max();
    //     }
    //     lookAt(Camera.eye, Camera.center, Camera.up);
    //     viewport(SCR_WIDTH / 8, SCR_HEIGHT / 8, SCR_WIDTH * 3 / 4, SCR_HEIGHT * 3 / 4);
    //     projection(-1.f / (Camera.eye - Camera.center).norm());

    //     Shader shader;

    //     for (int i = 0; i < model->nfaces(); i++) {
    //         for (int j = 0; j < 3; j++) {
    //             shader.vertexShader(i, j);
    //         }
    //         triangle(shader.varying_clipped_coords, shader, frame, z_buffer);
    //     }
    // }
    frame.flip_vertically();
    frame.write_tga_file("floor.tga");

    delete[] z_buffer;
    return 0;
}
