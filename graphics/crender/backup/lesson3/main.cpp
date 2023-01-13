#include <vector>
#include <cmath>
#include <string>

#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
#include "stb_image.h"

Vec3f light_dir(0, 0, -1);  // define light_dir
Model* model = NULL;
int texWidth, texHeight, nrChannels;
unsigned char* texture;

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 800;

void line(Vec2i v0, Vec2i v1, TGAImage& image, TGAColor color);
void triangle(Vec3f* positions, TGAImage& image, float* z_buffer, Vec2f* uvs, float itensity);
Vec3f barycentric(Vec3f v, Vec3f* positions);
TGAColor get_color_from_texture(unsigned char* texture, int width, int height, Vec2f uv);

/**
 * @brief Get the color from texture object
 *
 * @param texture
 * @param width 纹理的宽
 * @param height 纹理的高
 * @param u
 * @param v
 * @return Vec3f
 */
TGAColor get_color_from_texture(unsigned char* texture, int width, int height, Vec2f uv) {
    // 这里假设
    // stbi_image 在左上角，从上往下按行读取，每行中从左往右读取
    // uv 原点在左上角
    int R, G, B;
    unsigned char* start = texture;
    start += ((int)uv.x + (int)uv.y * width) * 3;
    R = (int)(*start);
    G = (int)(*(start + 1));
    B = (int)(*(start + 2));
    return TGAColor(R, G, B);
}

int main(int argc, char** argv) {
    TGAImage image(SCR_WIDTH, SCR_HEIGHT, TGAImage::RGB);
    /* 1. 初始化 */
    float z_buffer[SCR_WIDTH * SCR_HEIGHT];
    for (size_t x = 0; x < SCR_WIDTH; ++x) {
        for (size_t y = 0; y < SCR_HEIGHT; ++y) {
            z_buffer[y + SCR_WIDTH * x] = -std::numeric_limits<float>::max();
        }
    }
    model = new Model("../objs/african_head/african_head.obj");
    stbi_set_flip_vertically_on_load(true);
    texture = stbi_load("../objs/african_head/african_head_diffuse.tga", &texWidth, &texHeight, &nrChannels, 0);  // 字节数据版的纹理

    /* 3. 逐个三角形绘制 */
    for (size_t i = 0; i < model->nfaces(); ++i) {
        std::vector<int> vertIndexes = model->face(i);
        Vec3f screen_coords[3];
        Vec3f world_coords[3];
        Vec2f uv_coords[3];
        for (int j = 0; j < 3; j++) {
            Vec3f v = model->vert(vertIndexes[j]);
            world_coords[j] = v;
            screen_coords[j] = Vec3f(int((v.x + 1.) * SCR_WIDTH / 2. + .5), int((v.y + 1.) * SCR_HEIGHT / 2. + .5), v.z);
            uv_coords[j] = Vec2f(model->uv(i, j).x * texWidth, model->uv(i, j).y * texHeight);
        }
        Vec3f n = cross((world_coords[2] - world_coords[0]), (world_coords[1] - world_coords[0]));
        n.normalize();
        float intensity = n * light_dir;
        if (intensity > 0) {
            triangle(screen_coords, image, z_buffer, uv_coords, intensity);
        }
    }

    image.flip_vertically();  // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("lesson3_african_head.tga");
    stbi_image_free(texture);
    return 0;
}

void triangle(Vec3f* positions, TGAImage& image, float* z_buffer, Vec2f* uv_coords, float itensity) {
    // 1. bounding box
    int x_min = std::max(std::min(screen_coords[0].x, std::min(screen_coords[1].x, screen_coords[2].x)), 0.0f);
    int y_min = std::max(std::min(screen_coords[0].y, std::min(screen_coords[1].y, screen_coords[2].y)), 0.0f);
    int x_max = std::min(std::max(screen_coords[0].x, std::max(screen_coords[1].x, screen_coords[2].x)), SCR_WIDTH - 1.0f);
    int y_max = std::min(std::max(screen_coords[0].y, std::max(screen_coords[1].y, screen_coords[2].y)), SCR_HEIGHT - 1.0f);
    // 2. 判断点 (x, y) 是否在三角形内，如果是，则点亮像素
    Vec3f v(0.0f, 0.0f, 0.0f);
    Vec3f barycentric_coords(0.0f, 0.0f, 0.0f);
    TGAColor color(255, 255, 255, 255);
    Vec2f uv(0.0f, 0.0f);

    for (int x = x_min; x < x_max; ++x) {
        for (int y = y_min; y < y_max; ++y) {
            v.x = x;
            v.y = y;
            barycentric_coords = barycentric(v, positions);
            // 若在三角形内，应满足重心坐标 u,v,t>0 且 u+v+t=1
            if (barycentric_coords.x < 0 || barycentric_coords.y < 0 || barycentric_coords.z < 0) {
                continue;
            }
            v.z = positions[0].z * barycentric_coords.x + positions[1].z * barycentric_coords.y + positions[2].z * barycentric_coords.z;
            if (v.z > z_buffer[x + y * SCR_WIDTH]) {
                z_buffer[x + y * SCR_WIDTH] = v.z;
                for (size_t i = 0; i < 3; ++i) {
                    uv.x += barycentric_coords[i] * uv_coords[i].x;
                    uv.y += barycentric_coords[i] * uv_coords[i].y;
                }
                color = get_color_from_texture(texture, texWidth, texHeight, uv);
                color[0] *= itensity;
                color[1] *= itensity;
                color[2] *= itensity;
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