#include <vector>

#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
#include "our_gl.h"

Vec3f light_dir = Vec3f(0, 0, 1).normalize();
Model* model = NULL;

struct {
    Vec3f eye = Vec3f(1, 1, 3);
    Vec3f center = Vec3f(0, 0, 0);
    Vec3f up = Vec3f(0, 1, 0);
    float fovY = 45;
    float aspect_radio = 1;
    float near = -0.1;
    float far = 50.0;
} Camera;

/*
    Gouraud shading：插值计算三角形内颜色，shading
    Phong shading：插值计算三角形内法线，再计算颜色 shading
 */

// Phong-like shading
struct Shader : public IShader {
    mat<2, 3, float> varying_uv;    // fragment_uvs
    mat<4, 4, float> uniform_MVP;   // MVP transform
    mat<4, 4, float> uniform_MVPI;  // normal matrix

    virtual Vec4f vertex(int iface, int nthvert) {
        varying_uv.set_col(nthvert, model->uv(iface, nthvert));   // 读取 uvs
        Vec4f gl_Vertex = embed<4>(model->vert(iface, nthvert));  // 读取为齐次坐标
        return Viewport * Projection * ModelView * gl_Vertex;     // tranform to screen space
    }

    virtual bool fragment(Vec3f barycentric_coords, TGAColor& color) {
        // clipped space 不是 world space

        Vec2f uv = varying_uv * barycentric_coords;  // interpolation fragment_uv
        // ambient
        TGAColor ambientColor = TGAColor(5, 5, 5);

        // diffuse
        Vec3f normal = proj<3>(uniform_MVPI * embed<4>(model->normal(uv))).normalize();  // clipped space normal
        Vec3f light = proj<3>(uniform_MVP * embed<4>(light_dir)).normalize();            // clipped space light_dir
        float diff = std::max(0.0f, normal * light);                                     // 漫反射亮度系数
        TGAColor diffuseColor = model->diffuse(uv);

        // specular // 用的是平行光，无具体光源位置，也就无法计算 fragment2light
        Vec3f reflectLight = (normal * (normal * light * 2.f) - light).normalize();
        float spec = pow(std::max(reflectLight.z, 0.0f), model->specular(uv));  // 高光亮度系数

        for (size_t i = 0; i < 3; ++i) {
            color[i] = std::min<float>(ambientColor[i] + diffuseColor[i] * (0.6f * spec + diff), 255);
        }
        return false;
    }
};


int main(int argc, char** argv) {
    /* 1. 初始化 */
    model = new Model("../objs/african_head/african_head.obj");
    lookAt(Camera.eye, Camera.center, Camera.up);
    viewport(SCR_WIDTH / 8, SCR_HEIGHT / 8, SCR_WIDTH * 3 / 4, SCR_HEIGHT * 3 / 4);
    projection(-1.f / (Camera.eye - Camera.center).norm());
    light_dir.normalize();
    TGAImage image(SCR_WIDTH, SCR_HEIGHT, TGAImage::RGB);
    TGAImage z_buffer(SCR_WIDTH, SCR_HEIGHT, TGAImage::GRAYSCALE);

    Shader shader;
    shader.uniform_MVP = Projection * ModelView;
    shader.uniform_MVPI = (Projection * ModelView).invert_transpose();

    /* 3. 逐个三角形绘制 */
    for (size_t i = 0; i < model->nfaces(); ++i) {
        Vec4f screen_coords[3];

        for (int j = 0; j < 3; j++) {
            screen_coords[j] = shader.vertex(i, j);  // vertex shader
        }

        triangle(screen_coords, shader, image, z_buffer);
    }

    image.flip_vertically();  // to place the origin in the bottom left corner of the image
    z_buffer.flip_vertically();
    image.write_tga_file("6output.tga");
    z_buffer.write_tga_file("6zbuffer.tga");

    delete model;
    return 0;
}
