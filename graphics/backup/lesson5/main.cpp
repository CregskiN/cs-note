#include <vector>
#include <cmath>
#include <string>
#include <iostream>

#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
#include "stb_image.h"

Vec3f light_dir = Vec3f(0, 0, 1).normalize();
Model* model = NULL;
int texWidth, texHeight, nrChannels;
unsigned char* texture;

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 800;
const int SCR_DEPTH = 255;
struct {
    Vec3f eye = Vec3f(1, 1, 3);
    Vec3f center = Vec3f(0, 0, 0);
    Vec3f up = Vec3f(0, 1, 0);
    float fovY = 45;
    float aspect_radio = 1;
    float near = -0.1;
    float far = 50.0;
} Camera;

/**
 * @brief 将 [-1,1]*[-1,1]*[-1,1]映射到[x+width][y+width][0,SCR_DEPTH]
 *
 * @param screen_cube_x
 * @param screen_cube_y
 * @param width
 * @param height
 * @return Matrix
 */
Matrix viewport(int screen_cube_x, int screen_cube_y, int screen_cube_width, int screen_cube_height) {
    Matrix m = Matrix::identity(4);
    m[0][3] = screen_cube_x + screen_cube_width / 2.f;
    m[1][3] = screen_cube_y + screen_cube_height / 2.f;
    m[2][3] = SCR_DEPTH / 2.f;

    m[0][0] = screen_cube_width / 2.f;
    m[1][1] = screen_cube_height / 2.f;
    m[2][2] = SCR_DEPTH / 2.f;
    return m;
}

/**
 * @brief 生成观测矩阵
 *
 * @param eye 摄像机位置
 * @param center 摄像机观测的位置
 * @param up 上向量
 * @return Matrix
 */
Matrix lookAt(Vec3f eye, Vec3f center, Vec3f up) {
    Vec3f z = (eye - center).normalize();
    Vec3f x = (up ^ z).normalize();
    Vec3f y = (z ^ x).normalize();
    Matrix rotate = Matrix::identity(4);
    Matrix translate = Matrix::identity(4);
    for (int i = 0; i < 3; i++) {
        rotate[0][i] = x[i];
        rotate[1][i] = y[i];
        rotate[2][i] = z[i];
        rotate[i][3] = -center[i];
        // translate[i][3] = -(eye - center)[i]; // TODO: 这行是我推导的完全体 View，不知道为什么与原作者给出的代码不一致
    }
    return rotate * translate;
}

/**
 * @brief 计算重心坐标
 *
 * @param v
 * @param positions
 * @return Vec3f
 */
Vec3f barycentric(Vec3f v, Vec3f* positions) {
    Vec3f vec1 = Vec3f(positions[1].x - positions[0].x, positions[2].x - positions[0].x, positions[0].x - v.x);
    Vec3f vec2 = Vec3f(positions[1].y - positions[0].y, positions[2].y - positions[0].y, positions[0].y - v.y);
    Vec3f uv1 = vec1 ^ vec2;
    return std::abs(uv1.z) > 1e-2 ? Vec3f(1.0f - (uv1.x + uv1.y) / uv1.z, uv1.x / uv1.z, uv1.y / uv1.z) : Vec3f(-1, 1, 1);
}

void triangle(Vec3f screen_coords[3], TGAImage& image, int* z_buffer, Vec2f uv_coords[3], float itensities[3]) {
    // 1. bounding box
    int x_min = std::max(std::min(screen_coords[0].x, std::min(screen_coords[1].x, screen_coords[2].x)), 0.0f);
    int y_min = std::max(std::min(screen_coords[0].y, std::min(screen_coords[1].y, screen_coords[2].y)), 0.0f);
    int x_max = std::min(std::max(screen_coords[0].x, std::max(screen_coords[1].x, screen_coords[2].x)), SCR_WIDTH - 1.0f);
    int y_max = std::min(std::max(screen_coords[0].y, std::max(screen_coords[1].y, screen_coords[2].y)), SCR_HEIGHT - 1.0f);
    // 2. 判断点 (x, y) 是否在三角形内，如果是，则点亮像素
    Vec3i v(0, 0, 0);
    Vec3f barycentric_coords(0.0f, 0.0f, 0.0f);
    Vec2f uv(0.0f, 0.0f);
    float itensity = 0.0f;

    for (int x = x_min; x <= x_max; ++x) {
        for (int y = y_min; y <= y_max; ++y) {
            v.x = x;
            v.y = y;
            // 1. 判断是否在三角形内 by 重心坐标
            // barycentric_coords = barycentric(v, screen_coords);
            barycentric_coords = barycentric(v, screen_coords);
            if (barycentric_coords.x < 0 || barycentric_coords.y < 0 || barycentric_coords.z < 0) {
                continue;
            }
            // 2.1 插值计算 fragment depth，判断是否应该渲染
            v.z = screen_coords[0].z * barycentric_coords[0] + screen_coords[1].z * barycentric_coords[1] + screen_coords[2].z * barycentric_coords[2];
            if (v.z > z_buffer[x + y * SCR_WIDTH]) {
                z_buffer[x + y * SCR_WIDTH] = v.z;
                // 2.2 插值计算 fragment uv
                uv.x = uv_coords[0].x * barycentric_coords[0] + uv_coords[1].x * barycentric_coords[1] + uv_coords[2].x * barycentric_coords[2];
                uv.y = uv_coords[0].y * barycentric_coords[0] + uv_coords[1].y * barycentric_coords[1] + uv_coords[2].y * barycentric_coords[2];
                // 2.3 插值计算 fragment itensity
                //（也可以先计算 triangle vertex color 再插值 fragment color，这里是先计算 triganle vertex itensity，在插值 fragment itensity）
                itensity = itensities[0] * barycentric_coords[0] + itensities[1] * barycentric_coords[1] + itensities[2] * barycentric_coords[2];

                image.set(v.x, v.y, model->diffuse(Vec2i((int)uv.x, (int)uv.y)) * itensity);
            }
        }
    }
}

int main(int argc, char** argv) {
    TGAImage image(SCR_WIDTH, SCR_HEIGHT, TGAImage::RGB);
    /* 1. 初始化 */
    int z_buffer[SCR_WIDTH * SCR_HEIGHT];
    for (size_t x = 0; x < SCR_WIDTH; ++x) {
        for (size_t y = 0; y < SCR_HEIGHT; ++y) {
            z_buffer[y + SCR_WIDTH * x] = std::numeric_limits<int>::min();
        }
    }
    model = new Model("../objs/african_head/african_head.obj");
    stbi_set_flip_vertically_on_load(true);
    texture = stbi_load("../objs/african_head/african_head_diffuse.tga", &texWidth, &texHeight, &nrChannels, 0);  // 字节数据版的纹理
    std::cout << texWidth << "   " << texHeight << std::endl;
    Matrix ViewPort = Matrix::identity(4);
    Matrix Projection = Matrix::identity(4);
    Matrix ModelView = Matrix::identity(4);
    ModelView = lookAt(Camera.eye, Camera.center, Camera.up);
    Projection[3][2] = -1.f / (Camera.eye - Camera.center).norm();
    ViewPort = viewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    /* 3. 逐个三角形绘制 */
    for (size_t i = 0; i < model->nfaces(); ++i) {
        std::vector<int> faceVertexIds = model->face(i);
        Vec3f screen_coords[3];
        Vec2f uv_coords[3];
        float itensities[3];

        for (int j = 0; j < 3; j++) {
            Vec3f v = model->vert(faceVertexIds[j]);
            screen_coords[j] = Vec3f(ViewPort * Projection * ModelView * Matrix(v));
            uv_coords[j] = Vec2f(model->uv(i, j).x, model->uv(i, j).y);
            itensities[j] = model->norm(i, j) * light_dir;
        }

        triangle(screen_coords, image, z_buffer, uv_coords, itensities);
    }

    image.flip_vertically();  // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("lesson5_african_head.tga");
    stbi_image_free(texture);

    {  // dump z-buffer (debugging purposes only)
        TGAImage zbimage(SCR_WIDTH, SCR_HEIGHT, TGAImage::GRAYSCALE);
        for (int i = 0; i < SCR_WIDTH; i++) {
            for (int j = 0; j < SCR_HEIGHT; j++) {
                zbimage.set(i, j, TGAColor(z_buffer[i + j * SCR_WIDTH]));
            }
        }
        zbimage.flip_vertically();  // i want to have the origin at the left bottom corner of the image
        zbimage.write_tga_file("lesson5_zbuffer.tga");
    }
    return 0;
}
