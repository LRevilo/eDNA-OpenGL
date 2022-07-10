#pragma once

#include <glad/glad.h> // holds all OpenGL type declarations
#include "glm.h"
#include <string>
#include <vector>
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "MeshComponent.h"


struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    // mesh Data
    glm::dvec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;
    glm::mat4 transform;
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;
    unsigned int VAO;

    Mesh();

    // constructor
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    Mesh(std::vector<glm::vec3> positions, std::vector<unsigned int> indices);
    Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals);
    Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> uv);
    // render the mesh
    void Draw(Shader& shader, Camera &camera);
    void Draw(Shader& shader, Camera& camera, class Model& model);
    void DrawAsModelSection(Shader& shader, Camera& camera, Model& model);

    void UpdateTransform(glm::dvec3 modelPosition);
    glm::mat4 GetTransform();


private:
    // render data 
    unsigned int VBO, EBO;

    // initializes all the buffer objects/arrays
    void SetupMesh();

};
