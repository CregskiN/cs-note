#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <string>

#include "shader.h"
#include "stb_image.h"
#include "Model.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  // 窗口大小改变响应函数
void processInput(GLFWwindow* window);                                      // 键盘输入响应函数
void mouse_callback(GLFWwindow* window, double xpos, double ypos);          // 鼠标移动响应函数
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);   // 鼠标滑轮滚动响应函数

unsigned int loadTexture(char const* path);
unsigned int loadCubeMap(std::vector<std::string> faces);

// 摄像机相关参数
glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);  // Direction = - cameraFront
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// 屏幕
unsigned int SCR_WIDTH = 1400;
unsigned int SCR_HEIGHT = 1000;

float lastFrameTime = 0.0f;  // 上一帧时间点
float deltaTime = 0.0f;      // 当前与上一帧时间差
// 鼠标
bool firstMouse = true;
float lastX = 400;
float lastY = 300;
float pitch = 0.0f;
float yaw = -90.0f;
float fov = 45.0f;

// cube
glm::vec3 objectColor(1.0f, 0.5f, 0.31f);

int main() {
    // 初始化 GLFW 窗口
    glfwInit();                                                     // 初始化 GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  // OPENGL 主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                  // 次版本hao
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // Opengl Core 模式
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // mac

    // 初始化 GLFW window 对象，并将其设置为 GLFW 窗口上下文
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpengl", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);                               // 将窗口上下文，设置为当前线程上下文
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  // 设置 glfw 窗口捕捉鼠标光标

    // 初始化 GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);  // 设置 OPENGL 视口 viewpoit

    /*-- 注册事件对应的回调函数 --*/
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  // 注册：窗口尺寸改变响应函数
    glfwSetCursorPosCallback(window, mouse_callback);                   // 注册：鼠标移动响应函数
    glfwSetScrollCallback(window, scroll_callback);                     // 注册：鼠标滑轮滚动响应函数

    float quadVertices[] = {
        // 位置          // 颜色
        -0.05f, 0.05f, 1.0f, 0.0f, 0.0f,
        0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
        -0.05f, -0.05f, 0.0f, 0.0f, 1.0f,

        -0.05f, 0.05f, 1.0f, 0.0f, 0.0f,
        0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
        0.05f, 0.05f, 0.0f, 1.0f, 1.0f};

    unsigned int quadVAO, quadVBO;
    glGenBuffers(1, &quadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glGenVertexArrays(1, &quadVAO);
    glBindVertexArray(quadVAO);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    glm::vec2 translations[100];
    int index = 0;
    float offset = 0.1f;
    for (int y = -10; y < 10; y += 2) {
        for (int x = -10; x < 10; x += 2) {
            glm::vec2 translation;
            translation.x = (float)x / 10.0f + offset;
            translation.y = (float)y / 10.0f + offset;
            translations[index++] = translation;
        }
    }

    Shader shader("../shader.vert", "../shader.frag");

    shader.use();
    for (size_t i = 0; i < 100; ++i) {
        stringstream ss;
        string index;
        ss << i;
        index = ss.str();
        shader.setVec2(("offsets[" + index + "]").c_str(), translations[i]);
    }

    while (!glfwWindowShouldClose(window)) {
        // 0. 清屏
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // 清除 buffer 和 color 缓冲
        glEnable(GL_DEPTH_TEST);                             // 启用深度测试 z-buffer

        // 1. 处理键盘输入
        float currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;
        processInput(window);

        // 2. 渲染指令
        // glm::mat4 model = glm::mat4(1.0f);
        // glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
        // glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        glBindVertexArray(quadVAO);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);

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
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPosition += cameraSpeed * cameraFront;  // 往哪边去，就减哪边的方向向量
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPosition -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPosition += cameraSpeed * cameraUp;
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        cameraPosition -= cameraSpeed * cameraUp;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;  // 鼠标右移，xpos 增大
    float yoffset = lastY - ypos;  // 鼠标上移，ypos 减小
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    pitch += yoffset;
    yaw += xoffset;

    pitch = pitch > 89.0f ? 89.0f : pitch;
    pitch = pitch < -89.0f ? -89.0f : pitch;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}

unsigned int loadCubeMap(std::vector<std::string> faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 为避免在两张 2D 纹理边缘处无法集中 texel，用 GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}