# 运行此配置的cmake最低版本
cmake_minimum_required (VERSION 2.8.11) 
# 项目名称
project (Transformation)

link_directories("/usr/local/include")
# find_package(Eigen3 REQUIRED)
# include_directories(EIGEN3_INCLUDE_DIR)

# 生成目标文件：将名为 main.cpp 的文件编译成名为Transformation的可执行文件
add_executable (Transformation main.cpp)
