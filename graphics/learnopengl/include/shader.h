#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
   public:
    unsigned int ID;
    Shader(const char *vertexPath, const char *fragmentPath);
    // 激活 progarm
    void use();
    // uniform 工具函数
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, glm::mat4 value) const;
    void setVec3(const std::string &name, glm::vec3 value) const;

    void setTransormation(glm::mat4 model, glm::mat4 view, glm::mat4 projection) const;
    void setDirLight(const std::string &lightName, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) const;
    void setPointLight(const std::string &lightName, glm::vec3 position, float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specualr) const;
    void setSpotLight(const std::string &lightName, glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff, float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) const;
};

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    // 1. 从文件路径中读取 shader 代码
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // 打开文件
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        // std::cout << "asd" << std::endl;
        std::stringstream vShaderStream, fShaderStream;
        // 读取文件缓冲内容 到 数据流
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // 关闭文件处理器
        vShaderFile.close();
        fShaderFile.close();
        // 转换数据流到 string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    // 2. 编译着色器
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
    // 3. 链接着色器
    this->ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }
    // 4. 删除已经链接的着色器
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() {
    glUseProgram(this->ID);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}
void Shader::setMat4(const std::string &name, glm::mat4 value) const {
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::setVec3(const std::string &name, glm::vec3 value) const {
    glUniform3fv(glGetUniformLocation(this->ID, name.c_str()), 1, glm::value_ptr(value));
}
void Shader::setTransormation(glm::mat4 model, glm::mat4 view, glm::mat4 projection) const {
    this->setMat4("model", model);
    this->setMat4("view", view);
    this->setMat4("projection", projection);
}

void Shader::setDirLight(const std::string &lightName, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) const {
    this->setVec3(lightName + ".direction", direction);
    this->setVec3(lightName + ".ambient", ambient);
    this->setVec3(lightName + ".diffuse", diffuse);
    this->setVec3(lightName + ".specualr", specular);
}
void Shader::setPointLight(const std::string &lightName, glm::vec3 position, float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) const {
    this->setVec3(lightName + ".position", position);
    this->setFloat(lightName + ".constant", constant);
    this->setFloat(lightName + ".linear", linear);
    this->setFloat(lightName + ".quadratic", quadratic);
    this->setVec3(lightName + ".ambient", ambient);
    this->setVec3(lightName + ".diffuse", diffuse);
    this->setVec3(lightName + ".specualr", specular);
}
void Shader::setSpotLight(const std::string &lightName, glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff, float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) const {
    this->setVec3(lightName + ".position", position);
    this->setVec3(lightName + ".direction", direction);
    this->setFloat(lightName + ".cutOff", cutOff);
    this->setFloat(lightName + ".outerCutOff", outerCutOff);
    this->setFloat(lightName + ".constant", constant);
    this->setFloat(lightName + ".linear", linear);
    this->setFloat(lightName + ".quadratic", quadratic);
    this->setVec3(lightName + ".ambient", ambient);
    this->setVec3(lightName + ".diffuse", diffuse);
    this->setVec3(lightName + ".specualr", specular);
}

#endif