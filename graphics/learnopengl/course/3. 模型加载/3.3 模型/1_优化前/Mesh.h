#ifndef MESH_H
#define MESH_H
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 一个网格 Mash 包含一系列 Vertex、索引、material(纹理形式)
// 每个 Vertex 包含
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {  // 纹理数据
    unsigned int id;
    string type;  // 纹理类型：漫反射贴图、高光贴图...
    string path;
};

class Mesh {
   public:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    void Draw(Shader shader);

   private:
    unsigned int VAO, VBO, EBO;
    void setupMesh();
};

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    this->setupMesh();
}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->vertices.size() * sizeof(unsigned int), &this->vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Mesh::Draw(Shader shader) {
    unsigned int diffuseNumber = 1;
    unsigned int specularNumber = 1;
    for (size_t i = 0; i < textures.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        string number;
        string type = textures[i].type;
        /*
            uniform sampler2D texture_diffuse1;
            uniform sampler2D texture_diffuse2;
            uniform sampler2D texture_diffuse3;
            uniform sampler2D texture_specular1;
            uniform sampler2D texture_specular2;
         */
        if (type == "texture_diffuse")  // 针对漫反射贴图
            number = std::to_string(diffuseNumber++);
        else if (type == "texture.specular")  // 针对高光贴图
            number = std::to_string(specularNumber++);
        shader.setFloat(("material." + type + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

#endif