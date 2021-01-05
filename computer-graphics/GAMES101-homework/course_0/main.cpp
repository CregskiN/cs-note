#include <cmath>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <iostream>
int main() {

//   // Basic Example of cpp
//   std::cout << "Example of cpp \n";
//   float a = 1.0, b = 2.0;
//   std::cout << a << std::endl;                                 // 1
//   std::cout << a / b << std::endl;                             // 0.5
//   std::cout << std::sqrt(b) << std::endl;                      // 1.41421
//   std::cout << std::acos(-1) << std::endl;                     // 3.14159
//   std::cout << std::sin(30.0 / 180.0 * acos(-1)) << std::endl; // 0.5

//   // Example of vector
//   std::cout << "Example of vector \n";
//   // vector definition
//   Eigen::Vector3f v(1.0f, 2.0f, 3.0f);
//   Eigen::Vector3f w(1.0f, 0.0f, 0.0f);
//   // vector output
//   std::cout << "Example of output \n";
//   std::cout << v << std::endl; // 1 2 3
//   // vector add
//   std::cout << "Example of add \n";
//   std::cout << v + w << std::endl; // 2 2 3
//   // vector scalar multiply
//   std::cout << "Example of scalar multiply \n";
//   std::cout << v * 3.0f << std::endl; // 3 6 9
//   std::cout << 2.0f * v << std::endl; // 2 4 6

//   // Example of matrix
//   std::cout << "Example of matrix \n";
//   // matrix definition
//   Eigen::Matrix3f i, j;
//   i << 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;
//   j << 2.0, 3.0, 1.0, 4.0, 6.0, 5.0, 9.0, 7.0, 8.0;
//   // matrix output
//   std::cout << "Example of output \n";
//   std::cout << i << std::endl; // 1 2 3 // 4 5 6 // 7 8 9
//   // matrix add i + j
//   std::cout << i + j << std::endl; // 3 5 4 // 8 11 11 // 16 15 17
//   // matrix scalar multiply i * 2.0
//   std::cout << i * 2.0f << std::endl; // 2 4 6 // 8 10 12 // 14 16 18
//   // matrix multiply i * j
//   std::cout << i * j << std::endl; // 37 36 35 // 82 84 77 // 127 132 119
//   // matrix multiply vector i * v
//   std::cout << i * v << std::endl; // 14 32 50

  /*
   * PA 0
   *
   * 给定一个点 P =(2,1), 将该点绕原点先逆时针旋转 45◦，再平移 (1,2), 计算出
   * 变换后点的坐标(要求用齐次坐标进行计算)。
   */
  // TO DO: Define point P
  Eigen::Vector3f P(2.0f, 1.0f, 1.0f);
  // TO DO: Define rotation matrix M
  Eigen::Matrix3f M;
  float r = 45.0f;
  M << cos(r), sin(r), 0, -sin(r), cos(r), 0, 0, 0, 1;
  // TO DO: M * P
  std::cout << M * P << std::endl;
  return 0;
}