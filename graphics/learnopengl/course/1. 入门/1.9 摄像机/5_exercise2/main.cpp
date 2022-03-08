#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <math.h>

#include "shader.h"
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  // 窗口大小改变响应函数
void processInput(GLFWwindow* window);                                      // 键盘输入响应函数
void mouse_callback(GLFWwindow* window, double xpos, double ypos);          // 鼠标移动响应函数
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);   // 鼠标滑轮滚动响应函数
glm::mat4 _LookAt(glm::vec3 position, glm::vec3 front, glm::vec3 up);

// 摄像机相关参数
glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0, 0.0, -1.0f);  // Direction = - cameraFront
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
float lastFrameTime = 0.0f;  // 上一帧时间点
float deltaTime = 0.0f;      // 当前与上一帧时间差

float lastX = 400;
float lastY = 300;  // 鼠标上一帧位置
float pitch = 0.0f;
float yaw = -90.0f;
bool firstMouse = true;
float fov = 45.0f;

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

    Shader ourShader("../shader.vert", "../shader.frag");  // 相对路径从 可执行文件 的位置开始算，与 shell 的 pwd 无关
    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)};
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                         // 设置 buffer 类型
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  // 复制
    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);  //
    glEnableVertexAttribArray(0);                                                  // 应用到 location = 0                                                                    // 应用到 location = 1
    // 纹理属性
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture2"), 1);

    glEnable(GL_DEPTH_TEST);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // 0. 清屏
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);                // 设置颜色
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // 清除 buffer 和 color 缓冲

        // 1. 处理键盘输入
        float currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;
        processInput(window);

        // 2. 渲染指令
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        for (unsigned int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);

            glm::mat4 view = glm::mat4(1.0f);
            view = _LookAt(cameraPosition, cameraFront, cameraUp);

            glm::mat4 projection = glm::mat4(1.0f);
            projection = glm::perspective(glm::radians(fov), SCR_WIDTH / SCR_HEIGHT * 1.0f, 0.1f, 100.0f);

            unsigned int modelLocation = glGetUniformLocation(ourShader.ID, "model");
            unsigned int viewLocation = glGetUniformLocation(ourShader.ID, "view");
            unsigned int projectionLocation = glGetUniformLocation(ourShader.ID, "projection");

            ourShader.use();
            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // 3. 检查并调用事件，交换 framebuffer缓冲
        glfwPollEvents();         // 检查事件
        glfwSwapBuffers(window);  // 绘制 颜色buffer
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

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

glm::mat4 _LookAt(glm::vec3 position, glm::vec3 front, glm::vec3 worldUp) {
    glm::vec3 direction = -front;
    glm::vec3 right = glm::normalize(glm::cross(worldUp, direction));
    glm::vec3 up = glm::normalize(glm::cross(direction, right));

    glm::mat4 _trans = glm::mat4(1.0f);
    _trans[3][0] = -position.x;
    _trans[3][1] = -position.y;
    _trans[3][2] = -position.z;

    // glm [col][row]
    glm::mat4 _rotation = glm::mat4(1.0f);
    _rotation[0][0] = right.x;
    _rotation[1][0] = right.y;
    _rotation[2][0] = right.z;

    _rotation[0][1] = up.x;
    _rotation[1][1] = up.y;
    _rotation[2][1] = up.z;

    _rotation[0][2] = direction.x;
    _rotation[1][2] = direction.y;
    _rotation[2][2] = direction.z;

    return _rotation * _trans;
}