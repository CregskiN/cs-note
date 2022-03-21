# 1. 声明要求的cmake最低版本
cmake_minimum_required(VERSION 3.12)
# 1. 添加c++17标准支持
set(CMAKE_CXX_STANDARD 17)
# 1. 声明一个cmake工程
project(learnopengl)

message(STATUS "Project: learnopengl Start To Complie") # 打印相关消息消息

# 1. 头文件
include_directories(/usr/local/include)
include_directories(include)

link_directories(/usr/local/lib)

# aux_source_directory(. SRC_LIST) add_executable (learnopengl ${SRC_LIST})
add_executable(learnopengl main.cpp ./include/glad.c ./include/stb_image.cpp)

# 必须在添加可执行文件后 添加 link target_link_libraries(learnopengl glfw)
target_link_libraries(learnopengl -lglfw)
target_link_libraries(learnopengl -lassimp)
