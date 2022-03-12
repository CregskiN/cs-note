#ifndef MODEL_H
#define MODEL_H
#include <iostream>
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "shader.h"

using namespace std;

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class Model {
   public:
    Model(char *path, bool gamma) : gammaCorrection(gamma) { this->loadModel(path); };
    void Draw(Shader shader);
    vector<Texture> textures_loaded;
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;

   private:
    void loadModel(const string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *materials, aiTextureType type, string typeName);
};

void Model::Draw(Shader shader) {
    for (size_t i = 0; i < this->meshes.size(); ++i)
        meshes[i].Draw(shader);
}

/**
 * @brief 导入模型
 *
 * @param path
 */
void Model::loadModel(const string path) {
    // 1. assimp 导入模型
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);  // 图元三角化 | 反转纹理y轴
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
        return;
    }
    // 2. 遍历处理每个 node （递归）
    this->directory = path.substr(0, path.find_last_of('/'));
    this->processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    // 1. 遍历当前节点的 meshes，并做 processMesh 处理，后加入到当前 Model
    for (size_t i = 0; i < node->mNumMeshes; ++i) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        this->meshes.push_back(processMesh(mesh, scene));
    }
    // 2. 对子节点重复 1.
    for (size_t i = 0; i < node->mNumChildren; ++i)
        this->processNode(node->mChildren[i], scene);
};

/**
 * @brief 流程函数：从 assimp Mesh 中导入我们需要的数据
 *
 * @param mesh
 * @param scene
 * @return Mesh
 */
Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    // vertex // 顶点位置、法线、纹理坐标
    for (size_t i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vertex;
        vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        if (mesh->mTextureCoords[0])  // assimp 允许每个 mesh 有 8个 texcoords，这里只考虑第 1 个
            vertex.TexCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        else
            vertex.TexCoords = glm::vec2(0, 0);

        vertices.push_back(vertex);
    }
    // indices // 形成每个图元的顶点的索引
    for (size_t i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // material
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

/**
 * @brief 从 asssimp materials 中，导入指定 type 的 texture
 *
 * @param materials
 * @param type
 * @param typeName
 * @return vector<Texture>
 */
vector<Texture> Model::loadMaterialTextures(aiMaterial *materials, aiTextureType type, string typeName) {
    vector<Texture> textures;
    for (size_t i = 0; i < materials->GetTextureCount(type); ++i) {
        aiString str;
        materials->GetTexture(type, i, &str);
        bool skip = false;
        for (size_t j = 0; j < this->textures_loaded.size(); ++j) {
            // 如果这个 texture 已经添加到 textures_loaded，则使用已有结果，不用再从文件中读取
            if (std::strcmp(this->textures_loaded[j].path.data(), str.C_Str()) == 0) {
                textures.push_back(this->textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if (!skip) {
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            this->textures_loaded.push_back(texture);
        }
    }
    return textures;
}

/**
 * @brief 工具函数：从文件中提取 texture、设置纹理参数，返回 texture_id
 *
 * @param path
 * @param directory
 * @param gamma
 * @return unsigned int
 */
unsigned int TextureFromFile(const char *path, const string &directory, bool gamma) {
    string filename = string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
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

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

#endif