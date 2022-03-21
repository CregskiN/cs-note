#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

#include "shader.h"
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  // 窗口大小改变响应函数
void processInput(GLFWwindow* window);                                      // 键盘输入响应函数
void mouse_callback(GLFWwindow* window, double xpos, double ypos);          // 鼠标移动响应函数
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);   // 鼠标滑轮滚动响应函数

unsigned int loadTexture(char const* path);

// 摄像机相关参数
glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);  // Direction = - cameraFront
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// 屏幕
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

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

    /* vertexes */
    float cubeVertices[] = {
        // Back face // 背面
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  // Bottom-left
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,    // top-right
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,   // bottom-right // 顺时针
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,    // top-right
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  // bottom-left
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,   // top-left // 顺时针
        // Front face
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  // bottom-left
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   // bottom-right
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,    // top-right // 逆时针
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,    // top-right
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,   // top-left
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  // bottom-left // 逆时针
        // Left face
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    // top-right
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   // top-left
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  // bottom-left // 从右往左看 // 顺时针
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  // bottom-left
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   // bottom-right
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    // top-right
        // Right face
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    // top-left
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  // bottom-right
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   // top-right
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  // bottom-right
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    // top-left
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   // bottom-left
        // Bottom face
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  // top-right
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,   // top-left
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,    // bottom-left
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,    // bottom-left
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   // bottom-right
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  // top-right
        // Top face
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,  // top-left
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    // bottom-right
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   // top-right
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    // bottom-right
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,  // top-left
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f    // bottom-left
    };

    float planeVertices[] = {
        // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
        5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
        -5.0f, -0.5f, 5.0f, 0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f, 0.0f, 2.0f,

        5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f, 0.0f, 2.0f,
        5.0f, -0.5f, -5.0f, 2.0f, 2.0f};

    float quadVertices[] = {// vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
                            // positions   // texCoords
                            -1.0f, 1.0f, 0.0f, 1.0f,
                            -1.0f, -1.0f, 0.0f, 0.0f,
                            1.0f, -1.0f, 1.0f, 0.0f,

                            -1.0f, 1.0f, 0.0f, 1.0f,
                            1.0f, -1.0f, 1.0f, 0.0f,
                            1.0f, 1.0f, 1.0f, 1.0f};

    unsigned int cubeVAO, cubeVBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glBindVertexArray(cubeVAO);                                                    // 切换 cubeVAO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);  // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int planeVAO, planeVBO;
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
    glBindVertexArray(planeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);  // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    /* framebuffer */
    unsigned int framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    unsigned int texColorBuffer;
    glGenTextures(1, &texColorBuffer);
    glBindTexture(GL_TEXTURE_2D, texColorBuffer);  // 允许对 texColorBuffer 设置
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);  // 附加到当前绑定的帧缓冲对象
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    /* shader */
    Shader shader("../shader.vert", "../shader.frag");  // 盒子
    Shader screenShader("../screen_shader.vert", "../screen_shader.frag");

    /* texture */
    unsigned int cubeTexture = loadTexture("../textures/container.jpg");
    unsigned int floorTexture = loadTexture("../textures/metal.png");
    shader.use();
    shader.setInt("texture1", 0);
    screenShader.use();
    screenShader.setInt("screenTexture", 0);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window)) {
        // 0. 处理键盘输入
        float currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;
        processInput(window);

        // 1. 在自建帧中，绘制原场景
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        shader.use();
        /* cube */
        glEnable(GL_CULL_FACE);  // 启用面剔除
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        shader.setTransformation(model, view, projection);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cubeTexture);
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);  // 绘制 cube1
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        shader.setTransformation(model, view, projection);
        glDrawArrays(GL_TRIANGLES, 0, 36);  // 绘制 cube2
        glDisable(GL_CULL_FACE);

        /* plane */
        glBindVertexArray(planeVAO);
        glBindTexture(GL_TEXTURE_2D, floorTexture);
        shader.setTransformation(model, view, projection);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        // 2. 在默认帧中，渲染四边形
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        screenShader.use();
        glDisable(GL_DEPTH_TEST);
        glBindTexture(GL_TEXTURE_2D, texColorBuffer);
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // 3. 检查并调用事件，交换 framebuffer缓冲
        glfwPollEvents();         // 检查事件
        glfwSwapBuffers(window);  // 绘制 颜色buffer
    }
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &planeVAO);
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &planeVBO);
    glDeleteBuffers(1, &quadVBO);

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

unsigned int loadTexture(char const* path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        // if (format == GL_RGBA) {
            // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // } else {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}