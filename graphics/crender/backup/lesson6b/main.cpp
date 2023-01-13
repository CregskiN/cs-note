#include <vector>

#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
#include "our_gl.h"

Vec3f light_dir = Vec3f(0, 1, 3);
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
    mat<2, 3, float> varying_uv;         // vertex_uvs
    mat<4, 3, float> varying_positions;  // vertex_positions of clipped coordinates (not ndc)
    mat<3, 3, float> varying_normals;    // vertex_normals of clipped coordinates (not ndc)
    mat<3, 3, float> ndc_positions;      // vertex_positions of clipped coordinates (ndc)

    virtual Vec4f vertex(int iface, int nthvert) {
        varying_uv.set_col(nthvert, model->uv(iface, nthvert));
        varying_normals.set_col(nthvert, proj<3>((Projection * ModelView).invert_transpose() * embed<4>(model->normal(iface, nthvert), 0.f)));
        Vec4f gl_Vertex = Projection * ModelView * embed<4>(model->vert(iface, nthvert));
        varying_positions.set_col(nthvert, gl_Vertex);
        ndc_positions.set_col(nthvert, proj<3>(gl_Vertex / gl_Vertex[3]));  // projection division
        return gl_Vertex;
    }

    virtual bool fragment(Vec3f barycentric_coords, TGAColor& color) {
        Vec3f barycentric_normal = (varying_normals * barycentric_coords).normalize();
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

        Vec3f normal = (TBN * model->normal(uv)).normalize();

        float diff = std::max(0.f, normal * light_dir);
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
    TGAImage image(SCR_WIDTH, SCR_HEIGHT, TGAImage::RGB);
    light_dir = proj<3>((Projection * ModelView * embed<4>(light_dir, 0.f))).normalize();  // clipped space: light_dir
    float* z_buffer = new float[SCR_WIDTH * SCR_HEIGHT];
    for (size_t i = 0; i < SCR_WIDTH * SCR_HEIGHT; ++i)
        z_buffer[i] = -std::numeric_limits<float>::max();

    Shader shader;
    /* 3. 逐个三角形绘制 */
    for (size_t i = 0; i < model->nfaces(); ++i) {
        for (int j = 0; j < 3; j++) {
            shader.vertex(i, j);
        }

        triangle(shader.varying_positions, shader, image, z_buffer);
    }

    image.flip_vertically();
    image.write_tga_file("6output.tga");

    {  // dump z-buffer (debugging purposes only)
        TGAImage zbimage(SCR_WIDTH, SCR_HEIGHT, TGAImage::GRAYSCALE);
        for (size_t i = 0; i < SCR_WIDTH; ++i) {
            for (size_t j = 0; j < SCR_HEIGHT; ++j) {
                zbimage.set(i, j, TGAColor(z_buffer[i + j * SCR_WIDTH]));
            }
        }
        zbimage.flip_vertically();  // i want to have the origin at the left bottom corner of the image
        zbimage.write_tga_file("6zbuffer.tga");
    }

    delete model;
    delete[] z_buffer;
    return 0;
}
