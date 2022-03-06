#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

#include "shader.h"
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  // 窗口大小改变时的回调函数
void processInput(GLFWwindow* window);                                      // 处理键盘输入

float radio = 0, step = 0.01;

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
        // //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,    // 右上
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // 左下
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,   // 左上
    };
    unsigned int indices[] = {
        // 注意索引从0开始!
        0, 1, 3,  // 第一个三角形
        1, 2, 3   // 第二个三角形
    };
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                         // 设置 buffer 类型
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  // 复制
    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);  //
    glEnableVertexAttribArray(0);                                                  // 应用到 location = 0
    // 颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));  //
    glEnableVertexAttribArray(1);                                                                    // 应用到 location = 1
    // 纹理属性
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // 创建纹理，设置st纹理环绕方式、设置纹理过滤
    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 读入纹理图像、生成纹理
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);                                                // 反转y轴纹理
    unsigned char* data = stbi_load("../container.jpg", &width, &height, &nrChannels, 0);  // 图像路径、宽度、高度、通道数量
    if (data) {
        // target、MitMap级别、纹理储存格式（由图像格式决定）、宽高、0、图源格式、数据类型、图像数据
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    // 释放读入图像占用的内存
    stbi_image_free(data);

    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load("../awesomeface.png", &width, &height, &nrChannels, 0);
    if (data) {
        // target、MitMap级别、纹理储存格式（由图像格式决定）、宽高、0、图源格式、数据类型、图像数据
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    // 设置 uniform 之前必须激活
    ourShader.use();

    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
    ourShader.setInt("texture2", 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // 0. 清屏
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);  // 设置颜色
        glClear(GL_COLOR_BUFFER_BIT);          // 应用颜色到 color

        // 1. 处理键盘输入
        processInput(window);

        // 2. 渲染指令
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        ourShader.use();
        ourShader.setFloat("radio", radio);  // TODO: 按键盘输入调整 radio [0, 1]
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // 3. 检查并调用事件，交换 framebuffer缓冲
        glfwPollEvents();         // 检查事件
        glfwSwapBuffers(window);  // 绘制 颜色buffer
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // 关闭 glfw 窗口
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  // press esc
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {  // press up
        float tem = radio + step;
        radio = tem > 1 ? tem - 1 : tem;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {  // press down
        float tem = radio - step;
        radio = tem > 1 ? tem - 1 : tem;
    }
}