#include "Triangle.hpp"
#include "rasterizer.hpp"
#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <opencv2/opencv.hpp>

constexpr double MY_PI = 3.1415926;
// 给定三维下三个 点 v0(2.0,0.0,−2.0),v1(0.0,2.0,−2.0),v2(−2.0,0.0,−2.0),
// 你需要将这三个点的坐标变换为屏幕坐标并在屏幕上绘制出对应的线框三角形

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos) {
  Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

  Eigen::Matrix4f translate;
  translate << 1, 0, 0, -eye_pos[0], 0, 1, 0, -eye_pos[1], 0, 0, 1, -eye_pos[2],
      0, 0, 0, 1;

  view = translate * view;

  return view;
}

// rotation_angle 转动角度
Eigen::Matrix4f get_model_matrix(float rotation_angle) {
  Eigen::Matrix4f model = Eigen::Matrix4f::Identity();

  // TODO: Implement this function
  // Create the model matrix for rotating the triangle around the Z axis.
  // Then return it.
  float angle = rotation_angle * MY_PI / 180; // 角度 转 弧度
  model(0, 0) = cos(angle);
  model(0, 1) = -sin(angle);
  model(1, 0) = sin(angle);
  model(1, 1) = cos(angle);
  return model;
}

/**
 * 获取以axis轴（过原点）为中心的旋转矩阵
 */
Eigen::Matrix4f get_rotation(Eigen::Vector3f axis, float rotation_angle) {
  // Eigen::Matrix4f Rotation = Eigen::Matrix4f();
  // Eigen::Matrix4f Identity = Eigen::Matrix4f::Identity();
  // Eigen::Matrix4f N = Eigen::Matrix4f();
  // Eigen::Vector4f Axis = {axis(0,0), axis(1,0), axis(2,0), 0};
  // N << 0, -Axis(0, 0), Axis(1, 0), 0, 
  // Axis(2,0), 0, -Axis(0,0), 0, 
  // -Axis(1,0), Axis(0,0), 0, 0,
  // 0, 0, 0, 1;

  // Rotation = cos(rotation_angle)*Identity + (1-cos(rotation_angle))*axis*axis.transpose()+sin(rotation_angle)*N;
  // return Rotation;
}

// 给出可视角度、横纵比、Z轴近坐标、Z轴远坐标
Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
                                      float zNear, float zFar) {
  // Students will implement this function

  Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();

  // TODO: Implement this function
  // Create the projection matrix for the given parameters.
  // Then return it.

  float fov_rad = eye_fov * MY_PI / 180.0;
  float top = tan(fov_rad / 2.0) * abs(zNear);
  float right = top * aspect_ratio;
  float bottom = -top;
  float left = -right;

  Eigen::Matrix4f presp2ortho = Eigen::Matrix4f();
  presp2ortho << zNear, 0, 0, 0, 0, zNear, 0, 0, 0, 0, zNear + zFar,
      -zNear * zFar, 0, 0, -1, 0;            // 为什么这里是-1？
  Eigen::Matrix4f ortho = Eigen::Matrix4f(); // 先位移，再缩放
  Eigen::Matrix4f translate = Eigen::Matrix4f();
  Eigen::Matrix4f scale = Eigen::Matrix4f();
  scale << 2 / (right - left), 0, 0, 0, 0, 2 / (top - bottom), 0, 0, 0, 0,
      2 / (zNear - zFar), 0, 0, 0, 0, 1;
  translate << 1, 0, 0, -(right + left) / 2, 0, 1, 0, -(top + bottom) / 2, 0, 0,
      1, -(zNear + zFar) / 2, 0, 0, 0, 1;
  ortho = scale * translate;

  projection = ortho * presp2ortho;

  return projection;
}

int main(int argc, const char **argv) {
  float angle = 0;
  bool command_line = false;
  std::string filename = "output.png";

  if (argc >= 3) {
    command_line = true;
    angle = std::stof(argv[2]); // -r by default
    if (argc == 4) {
      filename = std::string(argv[3]);
    } else
      return 0;
  }

  rst::rasterizer r(700, 700);

  Eigen::Vector3f eye_pos = {0, 0, 5};

  std::vector<Eigen::Vector3f> pos{{2, 0, -2}, {0, 2, -2}, {-2, 0, -2}};

  std::vector<Eigen::Vector3i> ind{{0, 1, 2}};

  auto pos_id = r.load_positions(pos);
  auto ind_id = r.load_indices(ind);

  int key = 0;
  int frame_count = 0;

  if (command_line) {
    r.clear(rst::Buffers::Color | rst::Buffers::Depth);

    r.set_model(get_model_matrix(angle));
    r.set_view(get_view_matrix(eye_pos));
    r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

    r.draw(pos_id, ind_id, rst::Primitive::Triangle);
    cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
    image.convertTo(image, CV_8UC3, 1.0f);

    cv::imwrite(filename, image);

    return 0;
  }

  while (key != 27) {
    r.clear(rst::Buffers::Color | rst::Buffers::Depth);

    r.set_model(get_model_matrix(angle));
    r.set_view(get_view_matrix(eye_pos));
    r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

    r.draw(pos_id, ind_id, rst::Primitive::Triangle);

    cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
    image.convertTo(image, CV_8UC3, 1.0f);
    cv::imshow("image", image);
    key = cv::waitKey(10);

    std::cout << "frame count: " << frame_count++ << '\n';

    if (key == 'a') {
      angle += 10;
    } else if (key == 'd') {
      angle -= 10;
    }
  }

  return 0;
}
