#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);

Vec3f light_dir(0, 0, -1);  // define light_dir
Model* model = NULL;
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 800;

void line(Vec2i v0, Vec2i v1, TGAImage& image, TGAColor color);
void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage& image, TGAColor color);
bool _isInsideTriangle(Vec2i v, Vec2i v0, Vec2i v1, Vec2i v2);

int main(int argc, char** argv) {
    TGAImage image(SCR_WIDTH, SCR_HEIGHT, TGAImage::RGB);

    if (2 == argc) {
        model = new Model(argv[1]);
    } else {
        model = new Model("../obj/african_head.obj");
    }

    for (int i = 0; i < model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        Vec2i screen_coords[3];
        Vec3f world_coords[3];
        for (int j = 0; j < 3; j++) {
            Vec3f v = model->vert(face[j]);
            screen_coords[j] = Vec2i((v.x + 1.) * SCR_WIDTH / 2., (v.y + 1.) * SCR_HEIGHT / 2.);
            world_coords[j] = v;
        }
        Vec3f n = (world_coords[2] - world_coords[0]) ^ (world_coords[1] - world_coords[0]);
        n.normalize();
        float intensity = n * light_dir;
        if (intensity > 0) {
            triangle(screen_coords[0], screen_coords[1], screen_coords[2], image, TGAColor(intensity * 255, intensity * 255, intensity * 255, 255));
        }
    }

    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}

void triangle(Vec2i v0, Vec2i v1, Vec2i v2, TGAImage& image, TGAColor color) {
    // 1. bounding box
    int x_min = std::min(std::min(v0.x, 0), std::min(v1.x, v2.x));
    int y_min = std::min(std::min(v0.y, image.get_width() - 1), std::min(v1.y, v2.y));
    int x_max = std::max(v0.x, std::max(v1.x, v2.x));
    int y_max = std::max(v0.x, std::max(v1.y, v2.y));
    // 2. 判断点 (x, y) 是否在三角形内，如果是，则点亮像素
    for (int x = x_min; x < x_max; ++x) {
        for (int y = y_min; y < y_max; ++y) {
            if (_isInsideTriangle(Vec2i(x, y), v0, v1, v2))
                image.set(x, y, color);
        }
    }
}

void line(Vec2i v0, Vec2i v1, TGAImage& image, TGAColor color) {
    bool steep = false;
    int x0 = v0.x, y0 = v0.y;
    int x1 = v1.x, y1 = v1.y;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int y = y0;
    for (int x = x0; x <= x1; x++) {
        if (steep) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
        error2 += derror2;
        if (error2 > dx) {
            y += (y1 > y0 ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}

/**
 * @brief 判断点 v 是否在三角形 v0v1v2 内
 *
 * @param v
 * @param v0
 * @param v1
 * @param v2
 */
bool _isInsideTriangle(Vec2i v, Vec2i v0, Vec2i v1, Vec2i v2) {
    Vec2i v0v1 = v1 - v0;
    Vec2i v1v2 = v2 - v1;
    Vec2i v2v0 = v0 - v2;
    Vec2i v0v = v - v0;
    Vec2i v2v = v - v2;
    Vec2i v1v = v - v1;
    return (v0v1.x * v0v.y - v0v.x * v0v1.y) >= 0 && (v2v0.x * v2v.y - v2v.x * v2v0.y) >= 0 && (v1v2.x * v1v.y - v1v.x * v1v2.y) >= 0;
}
