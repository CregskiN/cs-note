#include <vector>
#include <limits>
#include <cstdlib>
#include <cmath>

#include "model.h"
#include "our_gl.h"

Matrix ModelView;
Matrix Viewport;
Matrix Projection;

IShader::~IShader() {}

/**
 * @brief 将 [-1,1]*[-1,1]*[-1,1]映射到[x+width][y+width][0,SCR_DEPTH]
 *
 * @param screen_cube_x
 * @param screen_cube_y
 * @param width
 * @param height
 * @return Matrix
 */
void viewport(int screen_cube_x, int screen_cube_y, int screen_cube_width, int screen_cube_height) {
    Viewport = Matrix::identity();
    Viewport[0][3] = screen_cube_x + screen_cube_width / 2.f;
    Viewport[1][3] = screen_cube_y + screen_cube_height / 2.f;
    Viewport[2][3] = 255.0f / 2.f;

    Viewport[0][0] = screen_cube_width / 2.f;
    Viewport[1][1] = screen_cube_height / 2.f;
    Viewport[2][2] = 255.0f / 2.f;
}

/**
 * @brief 生成观测矩阵
 *
 * @param eye 摄像机位置
 * @param center 摄像机观测的位置
 * @param up 上向量
 * @return Matrix
 */
void lookAt(Vec3f eye, Vec3f center, Vec3f up) {
    Vec3f z = (eye - center).normalize();
    Vec3f x = cross(up, z).normalize();
    Vec3f y = cross(z, x).normalize();
    Matrix rotate = Matrix::identity();
    Matrix translate = Matrix::identity();
    for (int i = 0; i < 3; i++) {
        rotate[0][i] = x[i];
        rotate[1][i] = y[i];
        rotate[2][i] = z[i];
        rotate[i][3] = -center[i];
        // translate[i][3] = -(eye - center)[i]; // TODO: 这行是我推导的完全体 View，不知道为什么与原作者给出的代码不一致
    }
    ModelView = rotate * translate;
}

void projection(float coeff) {
    Projection = Matrix::identity();
    Projection[3][2] = coeff;
}

/**
 * @brief 计算重心坐标
 *
 * @param v
 * @param positions
 * @return Vec3f
 */
Vec3f barycentric(Vec3f v, Vec4f* positions) {
    Vec3f vec1 = Vec3f(positions[1][0] - positions[0][0], positions[2][0] - positions[0][0], positions[0][0] - v.x);
    Vec3f vec2 = Vec3f(positions[1][1] - positions[0][1], positions[2][1] - positions[0][1], positions[0][1] - v.y);
    Vec3f uv1 = cross(vec1, vec2);
    return std::abs(uv1.z) > 1e-2 ? Vec3f(1.0f - (uv1.x + uv1.y) / uv1.z, uv1.x / uv1.z, uv1.y / uv1.z) : Vec3f(-1, 1, 1);
}

void triangle(Vec4f screen_coords[3], IShader& shader, TGAImage& image, float* z_buffer) {
    // 0. screen_coords 标准化
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            screen_coords[i][j] /= screen_coords[i][3];
        }
    }

    // 1. bounding box
    int x_min = std::max(std::min(screen_coords[0][0], std::min(screen_coords[1][0], screen_coords[2][0])), 0.0f);
    int y_min = std::max(std::min(screen_coords[0][1], std::min(screen_coords[1][1], screen_coords[2][1])), 0.0f);
    int x_max = std::min(std::max(screen_coords[0][0], std::max(screen_coords[1][0], screen_coords[2][0])), SCR_WIDTH - 1.0f);
    int y_max = std::min(std::max(screen_coords[0][1], std::max(screen_coords[1][1], screen_coords[2][1])), SCR_HEIGHT - 1.0f);

    // 2. 判断点 (x, y) 是否在三角形内，如果是，则点亮像素
    Vec3i v(0, 0, 0);
    TGAColor color;

    for (int x = x_min; x <= x_max; ++x) {
        for (int y = y_min; y <= y_max; ++y) {
            v.x = x;
            v.y = y;
            // 1. 判断是否在三角形内 by 重心坐标
            Vec3f barycentric_coords = barycentric(v, screen_coords);
            if (barycentric_coords.x < 0 || barycentric_coords.y < 0 || barycentric_coords.z < 0) {
                continue;
            }

            // 2.1 插值计算 fragment depth，判断是否应该渲染
            v.z = screen_coords[0][2] * barycentric_coords[0] + screen_coords[1][2] * barycentric_coords[1] + screen_coords[2][2] * barycentric_coords[2];
            float vw = screen_coords[0][3] * barycentric_coords[0] + screen_coords[1][3] * barycentric_coords[1] + screen_coords[2][3] * barycentric_coords[2];
            float frag_depth = std::max(0, std::min(255, (int)(v.z / vw + 0.5f)));
            // float frag_depth = v.z / vw;

            if (frag_depth > z_buffer[v.x + v.y * image.get_width()]) {
                bool discard = shader.fragmentShader(barycentric_coords, color);
                if (!discard) {                                            // 若该 fragment 无需 discard
                    z_buffer[v.x + v.y * image.get_width()] = frag_depth;  // 更新 z_buffer
                    image.set(v.x, v.y, color);                            // 更新 framebuffer
                }
            }
        }
    }
}