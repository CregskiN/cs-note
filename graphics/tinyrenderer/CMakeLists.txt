# 1. 声明要求的cmake最低版本
cmake_minimum_required(VERSION 3.12)
# 1. 添加c++17标准支持
set(CMAKE_CXX_STANDARD 11)
# 1. 声明一个cmake工程
project(tinyrenderer)

message(STATUS "Project: tinyrenderer Start To Complie") # 打印相关消息消息

# 1. 头文件
include_directories(/usr/local/include)
include_directories(include)
# link_directories(/usr/local/lib) link_directories(include)

# aux_source_directory(. SRC_LIST) add_executable (learnopengl ${SRC_LIST})
add_executable(tinyrenderer main.cpp ./include/tgaimage.cpp ./include/model.cpp
                            ./include/geometry.cpp ./include/our_gl.cpp)
# target_link_libraries(tinyrenderer -lModel)
