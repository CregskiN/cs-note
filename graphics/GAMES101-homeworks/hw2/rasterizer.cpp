//
// Created by goksu on 4/6/19.
//

#include "rasterizer.hpp"

#include <math.h>

#include <algorithm>
#include <opencv2/opencv.hpp>
#include <vector>

rst::pos_buf_id rst::rasterizer::load_positions(const std::vector<Eigen::Vector3f>& positions) {
    auto id = get_next_id();
    pos_buf.emplace(id, positions);

    return {id};
}

rst::ind_buf_id rst::rasterizer::load_indices(const std::vector<Eigen::Vector3i>& indices) {
    auto id = get_next_id();
    ind_buf.emplace(id, indices);

    return {id};
}

rst::col_buf_id rst::rasterizer::load_colors(const std::vector<Eigen::Vector3f>& cols) {
    auto id = get_next_id();
    col_buf.emplace(id, cols);

    return {id};
}

auto to_vec4(const Eigen::Vector3f& v3, float w = 1.0f) {
    return Vector4f(v3.x(), v3.y(), v3.z(), w);
}

static bool insideTriangle(float x, float y, const Vector3f* _v) {
    // TODO : Implement this function to check if the point (x, y) is inside the triangle represented by _v[0], _v[1], _v[2]
    Eigen::Vector3f P(x, y, 0);
    // 判断点P是否在三角形内，只需看 三个 边向量.cross(顶点2P向量) 的 z 坐标，是否同号， 叉乘结果_z = x1*y2 - x2*y1
    // 1. 准备边向量和点点向量
    Eigen::Vector3f v0_v1 = _v[1] - _v[0];
    Eigen::Vector3f v0_P = P - _v[0];

    Eigen::Vector3f v1_v2 = _v[2] - _v[1];
    Eigen::Vector3f v1_P = P - _v[1];

    Eigen::Vector3f v2_v0 = _v[0] - _v[2];
    Eigen::Vector3f v2_P = P - _v[2];

    // 2. 得出三个z
    float z_0 = v0_v1.x() * v0_P.y() - v0_P.x() * v0_v1.y();
    float z_1 = v1_v2.x() * v1_P.y() - v1_P.x() * v1_v2.y();
    float z_2 = v2_v0.x() * v2_P.y() - v2_P.x() * v2_v0.y();

    // 3. 判断是否同号，同号在在三角形内，否额不在
    return (z_0 > 0 && z_1 > 0 && z_2 > 0) || (z_0 < 0 && z_1 < 0 && z_2 < 0);
}

static std::tuple<float, float, float> computeBarycentric2D(float x, float y, const Vector3f* v) {
    float c1 = (x * (v[1].y() - v[2].y()) + (v[2].x() - v[1].x()) * y + v[1].x() * v[2].y() - v[2].x() * v[1].y()) / (v[0].x() * (v[1].y() - v[2].y()) + (v[2].x() - v[1].x()) * v[0].y() + v[1].x() * v[2].y() - v[2].x() * v[1].y());
    float c2 = (x * (v[2].y() - v[0].y()) + (v[0].x() - v[2].x()) * y + v[2].x() * v[0].y() - v[0].x() * v[2].y()) / (v[1].x() * (v[2].y() - v[0].y()) + (v[0].x() - v[2].x()) * v[1].y() + v[2].x() * v[0].y() - v[0].x() * v[2].y());
    float c3 = (x * (v[0].y() - v[1].y()) + (v[1].x() - v[0].x()) * y + v[0].x() * v[1].y() - v[1].x() * v[0].y()) / (v[2].x() * (v[0].y() - v[1].y()) + (v[1].x() - v[0].x()) * v[2].y() + v[0].x() * v[1].y() - v[1].x() * v[0].y());
    return {c1, c2, c3};
}

void rst::rasterizer::draw(pos_buf_id pos_buffer, ind_buf_id ind_buffer, col_buf_id col_buffer, Primitive type) {
    auto& buf = pos_buf[pos_buffer.pos_id];
    auto& ind = ind_buf[ind_buffer.ind_id];
    auto& col = col_buf[col_buffer.col_id];

    float f1 = (50 - 0.1) / 2.0;
    float f2 = (50 + 0.1) / 2.0;

    Eigen::Matrix4f mvp = projection * view * model;
    for (auto& i : ind) {
        Triangle t;
        Eigen::Vector4f v[] = {
            mvp * to_vec4(buf[i[0]], 1.0f),
            mvp * to_vec4(buf[i[1]], 1.0f),
            mvp * to_vec4(buf[i[2]], 1.0f)};
        //Homogeneous division
        for (auto& vec : v) {
            vec /= vec.w();
        }
        //Viewport transformation
        for (auto& vert : v) {
            vert.x() = 0.5 * width * (vert.x() + 1.0);
            vert.y() = 0.5 * height * (vert.y() + 1.0);
            vert.z() = vert.z() * f1 + f2;
        }

        for (int i = 0; i < 3; ++i) {
            t.setVertex(i, v[i].head<3>());
            t.setVertex(i, v[i].head<3>());
            t.setVertex(i, v[i].head<3>());
        }

        auto col_x = col[i[0]];
        auto col_y = col[i[1]];
        auto col_z = col[i[2]];

        t.setColor(0, col_x[0], col_x[1], col_x[2]);
        t.setColor(1, col_y[0], col_y[1], col_y[2]);
        t.setColor(2, col_z[0], col_z[1], col_z[2]);

        rasterize_triangle(t);
    }
}

//Screen space rasterization
void rst::rasterizer::rasterize_triangle(const Triangle& t) {
    auto v = t.toVector4();

    // TODO : Find out the bounding box of current triangle.
    // iterate through the pixel and find if the current pixel is inside the triangle
    // [l, r] * [b, t]
    float left = std::min(t.v[0](0), std::min(t.v[1](0), t.v[2](0)));
    float right = std::max(t.v[0](0), std::max(t.v[1](0), t.v[2](0)));
    float bottom = std::min(t.v[0](1), std::min(t.v[1](1), t.v[2](1)));
    float top = std::max(t.v[0](1), std::max(t.v[1](1), t.v[2](1)));

    int pattern = 1;
    switch (pattern) {
        case 0:  // 原渲染模式
            for (int x = left; x <= right; x++) {
                for (int y = bottom; y <= top; y++) {
                    if (insideTriangle(x + 0.5, y + 0.5, t.v)) {  // 如果在三角形内
                        // If so, use the following code to get the interpolated z value.
                        auto [alpha, beta, gamma] = computeBarycentric2D(x, y, t.v);
                        float w_reciprocal = 1.0 / (alpha / v[0].w() + beta / v[1].w() + gamma / v[2].w());
                        float z_interpolated = alpha * v[0].z() / v[0].w() + beta * v[1].z() / v[1].w() + gamma * v[2].z() / v[2].w();
                        z_interpolated *= w_reciprocal;

                        // TODO : set the current pixel (use the set_pixel function) to the color of the triangle (use getColor function) if it should be painted.
                        if (depth_buf[get_index(x, y)] > z_interpolated) {  // z 越大，距离观测点越近
                            Eigen::Vector3f color = t.getColor();
                            Eigen::Vector3f point(x, y, depth_buf[get_index(x, y)]);
                            depth_buf[get_index(x, y)] = z_interpolated;
                            set_pixel(point, color);
                        }
                    } else {  // 如果不在三角形内
                    }
                }
            }
            break;
        case 1:                    // MSAA
            float coverage = 0.0;  // 覆盖率
            for (int x = left; x <= right; x++) {
                for (int y = bottom; y <= top; y++) {
                    if (insideTriangle(x + 0.5, y + 0.5, t.v)) {
                        // 1. 如果像素 (x+0.5, y+0.5) 在三角形内
                        // 2. 计算 z value
                        auto [alpha, beta, gamma] = computeBarycentric2D(x, y, t.v);
                        float w_reciprocal = 1.0 / (alpha / v[0].w() + beta / v[1].w() + gamma / v[2].w());
                        float z_interpolated = alpha * v[0].z() / v[0].w() + beta * v[1].z() / v[1].w() + gamma * v[2].z() / v[2].w();
                        z_interpolated *= w_reciprocal;
                        if (depth_buf[get_index(x, y)] > z_interpolated) {
                            // 2. 如果 (x+0.5, y+0.5) 更近
                            coverage += insideTriangle(x + 0.25, y + 0.25, t.v) ? 0.25 : 0;
                            coverage += insideTriangle(x + 0.25, y + 0.75, t.v) ? 0.25 : 0;
                            coverage += insideTriangle(x + 0.75, y + 0.25, t.v) ? 0.25 : 0;
                            coverage += insideTriangle(x + 0.75, y + 0.75, t.v) ? 0.25 : 0;
                            // 3. 更新颜色和深度
                            Eigen::Vector3f color = t.getColor() * coverage;
                            Eigen::Vector3f point(x, y, depth_buf[get_index(x, y)]);
                            depth_buf[get_index(x, y)] = z_interpolated;
                            set_pixel(point, color);
                            coverage = 0.0;  // 覆盖率复位
                        }
                    }
                }
            }
            break;
    }
}

void rst::rasterizer::set_model(const Eigen::Matrix4f& m) {
    model = m;
}

void rst::rasterizer::set_view(const Eigen::Matrix4f& v) {
    view = v;
}

void rst::rasterizer::set_projection(const Eigen::Matrix4f& p) {
    projection = p;
}

void rst::rasterizer::clear(rst::Buffers buff) {
    if ((buff & rst::Buffers::Color) == rst::Buffers::Color) {
        std::fill(frame_buf.begin(), frame_buf.end(), Eigen::Vector3f{0, 0, 0});
    }
    if ((buff & rst::Buffers::Depth) == rst::Buffers::Depth) {
        std::fill(depth_buf.begin(), depth_buf.end(), std::numeric_limits<float>::infinity());
    }
}

rst::rasterizer::rasterizer(int w, int h) : width(w), height(h) {
    frame_buf.resize(w * h);
    depth_buf.resize(w * h);
}

int rst::rasterizer::get_index(int x, int y) {
    return (height - 1 - y) * width + x;
}

void rst::rasterizer::set_pixel(const Eigen::Vector3f& point, const Eigen::Vector3f& color) {
    //old index: auto ind = point.y() + point.x() * width;
    auto ind = (height - 1 - point.y()) * width + point.x();
    frame_buf[ind] = color;
}
