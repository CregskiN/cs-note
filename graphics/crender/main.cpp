#include <vector>
#include <iostream>
#include <time.h>
// #include <math.h>

#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
#include "sgl.h"

Vec3f light_dir = Vec3f(0, 1, 1).normalize();
Model* groundModel = NULL;
Model* mechModel = NULL;
Model* yinghamModel = NULL;

float* z_buffer = new float[SCR_WIDTH * SCR_HEIGHT];

// TODO: 模型分三类：
// ground = diffuse + roughness
// mech = diffuse + nm_tangent + roughness + spec
// yingham = diffuse + nm_tangent + roughness

// 基础着色器 = 透视矫正
// 法线着色器 = 透视矫正 + 法线切线贴图
struct GroundShader : public IShader {
    mat<2, 3, float> varying_uv;
    mat<3, 3, float> varying_normal;
    mat<4, 3, float> varying_clipped_coords;  // 4D列向量 * 3个

    virtual Vec4f vertexShader(int iface, int nthvert) {
        varying_uv.set_col(nthvert, groundModel->uv(iface, nthvert));
        varying_normal.set_col(nthvert, proj<3>((Projection * ModelView).invert_transpose() * embed<4>(groundModel->normal(iface, nthvert), .0f)));
        Vec4f gl_Vertex = Projection * ModelView * embed<4>(groundModel->vert(iface, nthvert) / 700.0f, 1.0f);
        varying_clipped_coords.set_col(nthvert, gl_Vertex);

        return gl_Vertex;
    }

    virtual bool fragmentShader(Vec3f barycentric_coords, TGAColor& color) {
        Vec2f uv = varying_uv * barycentric_coords;
        Vec3f normal = varying_normal * barycentric_coords;
        // float light = std::max<float>(light_dir * normal, 0.0f);
        // color = TGAColor(255, 255, 255) * light;
        TGAColor diffuse = groundModel->diffuse(uv);
        color = diffuse;
        return false;
    }
};

struct MechShader : public IShader {
    mat<2, 3, float> varying_uv;
    mat<3, 3, float> varying_normal;
    mat<4, 3, float> varying_clipped_coords;  // 4D列向量 * 3个
    mat<3, 3, float> ndc_positions;           // vertex_positions of clipped coordinates (ndc)

    virtual Vec4f vertexShader(int iface, int nthvert) {
        varying_uv.set_col(nthvert, mechModel->uv(iface, nthvert));
        varying_normal.set_col(nthvert, proj<3>((Projection * ModelView).invert_transpose() * embed<4>(mechModel->normal(iface, nthvert), .0f)));
        Vec4f gl_Vertex = Projection * ModelView * embed<4>(mechModel->vert(iface, nthvert) / 500.0f, 1.0f);
        varying_clipped_coords.set_col(nthvert, gl_Vertex);
        ndc_positions.set_col(nthvert, proj<3>(gl_Vertex / gl_Vertex[3]));  // projection division
        return gl_Vertex;
    }

    virtual bool fragmentShader(Vec3f barycentric_coords, TGAColor& color) {
        Vec3f barycentric_normal = (varying_normal * barycentric_coords).normalize();
        Vec2f uv = varying_uv * barycentric_coords;
        Vec3f pos = ndc_positions * barycentric_coords;

        mat<3, 3, float> A;
        A[0] = ndc_positions.col(1) - ndc_positions.col(0);
        A[1] = ndc_positions.col(2) - ndc_positions.col(0);
        A[2] = barycentric_normal;

        mat<3, 3, float> AI = A.invert();

        Vec3f T = (AI * Vec3f(varying_uv[0][1] - varying_uv[0][0], varying_uv[0][2] - varying_uv[0][0], 0)).normalize();
        Vec3f B = (AI * Vec3f(varying_uv[1][1] - varying_uv[1][0], varying_uv[1][2] - varying_uv[1][0], 0)).normalize();
        Vec3f N = cross(T, B);

        mat<3, 3, float> TBN;
        TBN.set_col(0, T);
        TBN.set_col(1, B);
        TBN.set_col(2, N);

        Vec3f normal = (TBN * mechModel->normal(uv)).normalize();

        TGAColor ambientColor = TGAColor(10, 10, 10);

        // Vec3f light = proj<3>(ModelView * embed<4>(light_dir)).normalize();  // clipped space light_dir
        Vec3f light = (light_dir - pos).normalize();
        float diff = std::max(0.0f, normal * light);  // 漫反射亮度系数
        TGAColor diffuseColor = mechModel->diffuse(uv) * (diff);

        Vec3f halfVector = ((light_dir - pos) + (Vec3f(0, 0, 0) - pos)).normalize();
        float spec = pow(std::max<float>(0.0f, normal * halfVector), 3.0f);

        TGAColor specularColor = TGAColor(mechModel->specular(uv), mechModel->specular(uv), mechModel->specular(uv)) * spec;

        for (size_t i = 0; i < 3; ++i) {
            color[i] = ambientColor[i] + diffuseColor[i] + specularColor[i];
        }
        return false;
    }
};

struct YinghamShader : public IShader {
    mat<2, 3, float> varying_uv;
    mat<3, 3, float> varying_normal;
    mat<4, 3, float> varying_clipped_coords;  // 4D列向量 * 3个
    mat<3, 3, float> ndc_positions;           // vertex_positions of clipped coordinates (ndc)
    virtual Vec4f vertexShader(int iface, int nthvert) {
        varying_uv.set_col(nthvert, yinghamModel->uv(iface, nthvert));
        varying_normal.set_col(nthvert, proj<3>((Projection * ModelView).invert_transpose() * embed<4>(yinghamModel->normal(iface, nthvert), .0f)));
        Vec4f gl_Vertex = Projection * ModelView * embed<4>(yinghamModel->vert(iface, nthvert) / 500.0f, 1.0f);
        varying_clipped_coords.set_col(nthvert, gl_Vertex);
        ndc_positions.set_col(nthvert, proj<3>(gl_Vertex / gl_Vertex[3]));  // projection division
        return gl_Vertex;
    }

    virtual bool fragmentShader(Vec3f barycentric_coords, TGAColor& color) {
        Vec3f barycentric_normal = (varying_normal * barycentric_coords).normalize();
        Vec2f uv = varying_uv * barycentric_coords;

        mat<3, 3, float> A;
        A[0] = ndc_positions.col(1) - ndc_positions.col(0);
        A[1] = ndc_positions.col(2) - ndc_positions.col(0);
        A[2] = barycentric_normal;

        mat<3, 3, float> AI = A.invert();

        Vec3f T = (AI * Vec3f(varying_uv[0][1] - varying_uv[0][0], varying_uv[0][2] - varying_uv[0][0], 0)).normalize();
        Vec3f B = (AI * Vec3f(varying_uv[1][1] - varying_uv[1][0], varying_uv[1][2] - varying_uv[1][0], 0)).normalize();
        Vec3f N = cross(T, B);

        mat<3, 3, float> TBN;
        TBN.set_col(0, T);
        TBN.set_col(1, B);
        TBN.set_col(2, N);

        Vec3f normal = (TBN * yinghamModel->normal(uv)).normalize();

        TGAColor ambientColor = TGAColor(5, 5, 5);
        Vec3f light = proj<3>(Projection * ModelView * embed<4>(light_dir)).normalize();  // clipped space light_dir
        float diff = std::max(0.0f, normal * light);                                      // 漫反射亮度系数
        TGAColor diffuseColor = yinghamModel->diffuse(uv);
        // specular // 用的是平行光，无具体光源位置，也就无法计算 fragment2light
        Vec3f reflectLight = (normal * (normal * light * 2.f) - light).normalize();
        float spec = pow(std::max(reflectLight.z, 0.0f), yinghamModel->specular(uv));  // 高光亮度系数
        for (size_t i = 0; i < 3; ++i) {
            color[i] = std::min<float>(ambientColor[i] + diffuseColor[i] * (0.6 * spec + diff), 255);
        }
        return false;
    }
};

int main(int argc, char** argv) {
    // 1. 初始化 z-buffer
    std::cout << "初始化开始..." << std::endl;
    for (size_t i = 0; i < SCR_WIDTH * SCR_HEIGHT; ++i) {
        z_buffer[i] = -std::numeric_limits<float>::max();
    }
    lookAt(Camera.eye, Camera.center, Camera.up);
    viewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    projection(-1.f / (Camera.eye - Camera.center).norm());
    mechModel = new Model("../objs/dieselpunk/mech.obj");
    yinghamModel = new Model("../objs/dieselpunk/yingham.obj");
    TGAImage frame(SCR_WIDTH, SCR_HEIGHT, TGAImage::RGB);
    std::cout << "初始化完毕，开始绘制。" << std::endl;
    // 2. 绘制
    // {
    //     model = new Model("../objs/dieselpunk/ground.obj");
    //     GroundShader shader;
    //     for (int i = 0; i < model->nfaces(); i++) {
    //         for (int j = 0; j < 3; j++) {
    //             shader.vertexShader(i, j);
    //         }
    //         triangle(shader.varying_clipped_coords, shader, frame, z_buffer);
    //     }
    // }
    clock_t startTime = clock();
    {
        MechShader shader;

        for (int i = 0; i < mechModel->nfaces(); i++) {
            for (int j = 0; j < 3; j++) {
                shader.vertexShader(i, j);
            }
            triangle(shader.varying_clipped_coords, shader, frame, z_buffer);
        }
    }

    {
        YinghamShader shader;

        for (int i = 0; i < yinghamModel->nfaces(); i++) {
            for (int j = 0; j < 3; j++) {
                shader.vertexShader(i, j);
            }
            triangle(shader.varying_clipped_coords, shader, frame, z_buffer);
        }
    }
    clock_t endTime = clock();
    double totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    std::cout << "渲染完毕，耗时: " << totalTime << " " << std::endl;

    frame.flip_vertically();
    frame.write_tga_file("output.tga");

    delete groundModel;
    delete mechModel;
    delete yinghamModel;
    delete[] z_buffer;
    return 0;
}
