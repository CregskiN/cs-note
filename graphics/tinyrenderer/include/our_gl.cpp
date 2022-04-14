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
    }
    ModelView = rotate * translate;
}

void projection(float coeff) {
    Projection = Matrix::identity();
    Projection[3][2] = coeff;
}

Vec3f barycentric(Vec2f A, Vec2f B, Vec2f C, Vec2f P) {
    Vec3f s[2];
    for (int i = 2; i--;) {
        s[i][0] = C[i] - A[i];
        s[i][1] = B[i] - A[i];
        s[i][2] = A[i] - P[i];
    }
    Vec3f u = cross(s[0], s[1]);
    if (std::abs(u[2]) > 1e-2)  // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
        return Vec3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
    return Vec3f(-1, 1, 1);  // in this case generate negative coordinates, it will be thrown away by the rasterizator
}

/**
 * @brief
 *
 * @param clipped_coords 未做透视除法(标准化)的 clipped coordinates
 * @param shader
 * @param image
 * @param z_buffer
 */

void triangle(mat<4, 3, float> &clipped_coords, IShader &shader, TGAImage &image, float *z_buffer) {
    mat<3, 4, float> screen_coords = (Viewport * clipped_coords).transpose();
    mat<3, 2, float> ndc_screen_coords;
    for (size_t i = 0; i < 3; ++i)
        ndc_screen_coords[i] = proj<2>(screen_coords[i] / screen_coords[i][3]);

    // 1. bounding box
    int x_min = std::max(std::min(ndc_screen_coords[0][0], std::min(ndc_screen_coords[1][0], ndc_screen_coords[2][0])), 0.0f);
    int y_min = std::max(std::min(ndc_screen_coords[0][1], std::min(ndc_screen_coords[1][1], ndc_screen_coords[2][1])), 0.0f);
    int x_max = std::min(std::max(ndc_screen_coords[0][0], std::max(ndc_screen_coords[1][0], ndc_screen_coords[2][0])), SCR_WIDTH - 1.0f);
    int y_max = std::min(std::max(ndc_screen_coords[0][1], std::max(ndc_screen_coords[1][1], ndc_screen_coords[2][1])), SCR_HEIGHT - 1.0f);

    // 2. 判断点 (x, y) 是否在三角形内，如果是，则点亮像素
    Vec2i v(0, 0);
    TGAColor color;

    for (int x = x_min; x <= x_max; ++x) {
        for (int y = y_min; y <= y_max; ++y) {
            v.x = x;
            v.y = y;

            // 1. 判断是否在三角形内 by 重心坐标
            Vec3f barycentric_screen = barycentric(ndc_screen_coords[0], ndc_screen_coords[1], ndc_screen_coords[2], v);
            if (barycentric_screen.x < 0 || barycentric_screen.y < 0 || barycentric_screen.z < 0) {
                continue;
            }

            // 2.1 插值计算 fragment depth，判断是否应该渲染
            Vec3f barycentric_clipped = Vec3f(barycentric_screen.x / screen_coords[0][3], barycentric_screen.y / screen_coords[1][3], barycentric_screen.z / screen_coords[2][3]);
            barycentric_clipped = barycentric_clipped / (barycentric_clipped.x + barycentric_clipped.y + barycentric_clipped.z);

            float frag_depth = std::min<float>(clipped_coords[2] * barycentric_clipped * 255, 255);
            float old_depth = z_buffer[v.x + v.y * image.get_width()];

            if (frag_depth > old_depth) {
                bool discard = shader.fragment(barycentric_clipped, color);
                if (!discard) {                                            // 若该 fragment 无需 discard
                    z_buffer[v.x + v.y * image.get_width()] = frag_depth;  // 更新 z_buffer
                    image.set(v.x, v.y, color);                            // 更新 framebuffer
                }
            }
        }
    }
}