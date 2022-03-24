#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);

Vec3f light_dir(0, 0, -1);  // define light_dir
Model* model = NULL;
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 800;

void line(Vec2i v0, Vec2i v1, TGAImage& image, TGAColor color);
void triangle(Vec3f* positions, TGAImage& image, TGAColor color, float* z_buffer);
Vec3f barycentric(Vec3f v, Vec3f* positions);

int main(int argc, char** argv) {
    TGAImage image(SCR_WIDTH, SCR_HEIGHT, TGAImage::RGB);
    /* 1. 初始化 */
    float z_buffer[SCR_WIDTH * SCR_HEIGHT];
    for (size_t x = 0; x < SCR_WIDTH; ++x) {
        for (size_t y = 0; y < SCR_HEIGHT; ++y) {
            z_buffer[y + SCR_WIDTH + x] = -std::numeric_limits<float>::max();
        }
    }
    model = new Model("../obj/african_head.obj");

    /* 3. 逐个三角形绘制 */
    for (size_t i = 0; i < model->nfaces(); ++i) {
        std::vector<int> face = model->face(i);
        Vec3f screen_coords[3];
        Vec3f world_coords[3];
        for (int j = 0; j < 3; j++) {
            Vec3f v = model->vert(face[j]);
            world_coords[j] = v;
            screen_coords[j] = Vec3f(int((v.x + 1.) * SCR_WIDTH / 2. + 0.5f), int((v.y + 1.) * SCR_HEIGHT / 2. + 0.5f), v.z);  // 0.5 为像素中心
        }
        Vec3f n = cross((world_coords[2] - world_coords[0]), (world_coords[1] - world_coords[0]));
        n.normalize();
        float intensity = n * light_dir;
        if (intensity > 0) {
            triangle(screen_coords, image, TGAColor(intensity * 255, intensity * 255, intensity * 255, 255), z_buffer);
        }
    }

    image.flip_vertically();  // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}

void triangle(Vec3f* positions, TGAImage& image, TGAColor color, float* z_buffer) {
    // 1. bounding box
    int x_min = std::min(std::min(positions[0].x, 0.0f), std::min(positions[1].x, positions[2].x));
    int y_min = std::min(std::min(positions[0].y, SCR_HEIGHT - 1.0f), std::min(positions[1].y, positions[2].y));
    int x_max = std::max(positions[0].x, std::max(positions[1].x, positions[2].x));
    int y_max = std::max(positions[0].y, std::max(positions[1].y, positions[2].y));
    // 2. 判断点 (x, y) 是否在三角形内，如果是，则点亮像素
    Vec3f v(0.0f, 0.0f, 0.0f);
    for (int x = x_min; x < x_max; ++x) {
        for (int y = y_min; y < y_max; ++y) {
            v.x = x;
            v.y = y;
            Vec3f bc = barycentric(v, positions);
            // 若在三角形内，应满足重心坐标 u,v,t>0 且 u+v+t=1
            if (bc.x < 0 || bc.y < 0 || bc.z < 0) {
                continue;
            }
            v.z = positions[0].z * bc.x + positions[1].z * bc.y + positions[2].z * bc.z;
            if (v.z > z_buffer[x + y * SCR_WIDTH]) {
                z_buffer[x + y * SCR_WIDTH] = v.z;
                image.set(x, y, color);
            }
        }
    }
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
    Vec3f uv1 = cross(vec1, vec2);
    return std::abs(uv1.z) > 1e-2 ? Vec3f(1.0f - (uv1.x + uv1.y) / uv1.z, uv1.x / uv1.z, uv1.y / uv1.z) : Vec3f(-1, 1, 1);
}
