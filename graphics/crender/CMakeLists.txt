# 1. 声明要求的cmake最低版本
cmake_minimum_required(VERSION 3.12)
# 1. 添加c++17标准支持
set(CMAKE_CXX_STANDARD 11)
# 1. 声明一个cmake工程
project(crender)

message(STATUS "Project: crender Start To Complie") # 打印相关消息消息

# 1. 头文件
include_directories(/usr/local/include)
include_directories(core)

# set(HEADERS core/geometry.h core/model.h core/sgl.h core/tgaimage.h)

set(SOURCES core/geometry.cpp core/model.cpp core/sgl.cpp core/tgaimage.cpp)

add_executable(crender main.cpp ${SOURCES})
