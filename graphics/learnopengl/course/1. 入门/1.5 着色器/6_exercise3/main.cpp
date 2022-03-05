#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  // 窗口大小改变时的回调函数
void processInput(GLFWwindow* window);                                      // 处理键盘输入

int main() {
    // 初始化 GLFW 窗口
    glfwInit();                                                     // 初始化 GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  // OPENGL 主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                  // 次版本hao
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // Opengl Core 模式
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // mac

    // 初始化 GLFW window 对象，并将其设置为 GLFW 窗口上下文
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpengl", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);  // 将窗口上下文，设置为当前线程上下文

    // 初始化 GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);  // 设置 OPENGL 视口 viewpoit

    /*-- 注册事件对应的回调函数 --*/
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  // 注册：当窗口改变时的回调函数

    Shader ourShader("../shader.vert", "../shader.frag");  // 相对路径从 可执行文件 的位置开始算，与 shell 的 pwd 无关

    float vertices[] = {
        // 位置              // 颜色
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // 左下
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f     // 顶部
    };
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                         // 设置 buffer 类型
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  // 复制
    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);  //
    glEnableVertexAttribArray(0);                                                  // 应用到 location = 0
    // 颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));  //
    glEnableVertexAttribArray(1);                                                                    // 应用到 location = 1

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // 0. 清屏
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);  // 设置颜色
        glClear(GL_COLOR_BUFFER_BIT);          // 应用颜色到 color

        // 1. 处理键盘输入
        processInput(window);

        // 2. 渲染指令
        // 激活着色器
        ourShader.use();

        // 绘制
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // 3. 检查并调用事件，交换 framebuffer缓冲
        glfwPollEvents();         // 检查事件
        glfwSwapBuffers(window);  // 绘制 颜色buffer
    }

    // 关闭 glfw 窗口
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  // 如果按下 esc // 另一种是 释放 esc
        glfwSetWindowShouldClose(window, true);
}