# 1. 声明要求的cmake最低版本
cmake_minimum_required( VERSION 3.12 )
# 2. 添加c++17标准支持
set( CMAKE_CXX_STANDARD 17 )
# 3. 声明一个cmake工程
PROJECT(learnopengl)

MESSAGE(STATUS "Project: learnopengl Start To Complie") #打印相关消息消息

# 4. 头文件
include_directories(/usr/local/include)
include_directories(/Users/cregskin/code/cs-note/graphics/learnopengl/include)

# set(SRC ${PROJECT_SOURCE_DIR}/main.cpp)

find_package(glfw3 REQUIRED)
# find_package(glad REQUIRED)

# aux_source_directory(. SRC_LIST)
# add_executable (learnopengl ${SRC_LIST})
add_executable (learnopengl main.cpp ./include/glad.c ./include/stb_image.cpp )

target_link_libraries(learnopengl glfw)
# target_link_libraries(learnopengl glad)
# 必须在添加可执行文件后 添加 link