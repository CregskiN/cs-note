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
    mat<2, 3, float> varying_uv;   // triangle uv coordinates, written by the vertex shader, read by the fragment shader
    mat<4, 3, float> varying_tri;  // triangle coordinates (clip coordinates), written by VS, read by FS
    mat<3, 3, float> varying_nrm;  // normal per vertex to be interpolated by FS
    mat<3, 3, float> ndc_tri;      // triangle in normalized device coordinates

    virtual Vec4f vertex(int iface, int nthvert) {
        varying_uv.set_col(nthvert, model->uv(iface, nthvert));
        varying_nrm.set_col(nthvert, proj<3>((Projection * ModelView).invert_transpose() * embed<4>(model->normal(iface, nthvert), 0.f)));
        Vec4f gl_Vertex = Projection * ModelView * embed<4>(model->vert(iface, nthvert));
        varying_tri.set_col(nthvert, gl_Vertex);
        ndc_tri.set_col(nthvert, proj<3>(gl_Vertex / gl_Vertex[3]));
        return gl_Vertex;
    }

    virtual bool fragment(Vec3f bar, TGAColor& color) {
        Vec3f bn = (varying_nrm * bar).normalize();
        Vec2f uv = varying_uv * bar;

        mat<3, 3, float> A;
        A[0] = ndc_tri.col(1) - ndc_tri.col(0);
        A[1] = ndc_tri.col(2) - ndc_tri.col(0);
        A[2] = bn;

        mat<3, 3, float> AI = A.invert();

        Vec3f i = AI * Vec3f(varying_uv[0][1] - varying_uv[0][0], varying_uv[0][2] - varying_uv[0][0], 0);
        Vec3f j = AI * Vec3f(varying_uv[1][1] - varying_uv[1][0], varying_uv[1][2] - varying_uv[1][0], 0);

        mat<3, 3, float> B;
        B.set_col(0, i.normalize());
        B.set_col(1, j.normalize());
        B.set_col(2, bn);

        Vec3f n = (B * model->normal(uv)).normalize();

        float diff = std::max(0.f, n * light_dir);
        color = model->diffuse(uv) * diff;

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
    light_dir = proj<3>((Projection * ModelView * embed<4>(light_dir, 0.f))).normalize();  // clipped space: light_dir

    Shader shader;

    /* 3. 逐个三角形绘制 */
    for (size_t i = 0; i < model->nfaces(); ++i) {
        for (int j = 0; j < 3; j++) {
            shader.vertex(i, j);
        }

        triangle(shader.varying_tri, shader, image, z_buffer);
    }

    image.flip_vertically();
    z_buffer.flip_vertically();
    image.write_tga_file("6output.tga");
    z_buffer.write_tga_file("6zbuffer.tga");

    delete model;
    return 0;
}
