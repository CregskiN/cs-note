#ifndef MESH_H
#define MESH_H
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define MAX_BONE_INFLUENCE 4

// 一个网格 Mash 包含一系列 Vertex、索引、material(纹理形式)
// 每个 Vertex 包含
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;

    glm::vec3 Tangent;
    glm::vec3 Bitangent;
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    float m_Weights[MAX_BONE_INFLUENCE];
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
    glGenVertexArrays(1, &(this->VAO));
    glGenBuffers(1, &(this->VBO));
    glGenBuffers(1, &(this->EBO));

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &(this->vertices[0]), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), &(this->indices[0]), GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    // normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);
    // texture coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    glEnableVertexAttribArray(3);
    // vertex bitangent
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
    glEnableVertexAttribArray(4);
    // ids
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));
    glEnableVertexAttribArray(5);
    // weights
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));
    glEnableVertexAttribArray(6);

    glBindVertexArray(0);
}

void Mesh::Draw(Shader shader) {
    unsigned int diffuseNumber = 1;
    unsigned int specularNumber = 1;
    unsigned int normalNumber = 1;
    unsigned int heightNumber = 1;
    unsigned int reflectionNumber = 1;

    for (size_t i = 0; i < textures.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        string number;
        string type = textures[i].type;
        if (type == "texture_diffuse")  // 针对漫反射贴图
            number = std::to_string(diffuseNumber++);
        else if (type == "texture.specular")  // 针对高光贴图
            number = std::to_string(specularNumber++);
        else if (type == "texture_normal")
            number = std::to_string(normalNumber++);
        else if (type == "texture_height")
            number = std::to_string(heightNumber++);
        else if (type == "texture_reflection")
            number = std::to_string(reflectionNumber++);

        shader.setFloat(("material." + type + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    // 绘制 Mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

#endif