#pragma once
#include "Model.h"
class CubeModel :
    public Model
{

public:
    

    CubeModel();

    std::vector<glm::vec3> cube_vertices = {
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f,  0.5f, -0.5f),
        glm::vec3(0.5f,  0.5f, -0.5f),
        glm::vec3(-0.5f,  0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),

        glm::vec3(-0.5f, -0.5f,  0.5f),
        glm::vec3(0.5f, -0.5f,  0.5f),
        glm::vec3(0.5f,  0.5f,  0.5f),
        glm::vec3(0.5f,  0.5f,  0.5f),
        glm::vec3(-0.5f,  0.5f,  0.5f),
        glm::vec3(-0.5f, -0.5f,  0.5f),

        glm::vec3(-0.5f,  0.5f,  0.5f),
        glm::vec3(-0.5f,  0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f,  0.5f),
        glm::vec3(-0.5f,  0.5f,  0.5f),

        glm::vec3(0.5f,  0.5f,  0.5f),
        glm::vec3(0.5f,  0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f,  0.5f),
        glm::vec3(0.5f,  0.5f,  0.5f),

        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f,  0.5f),
        glm::vec3(0.5f, -0.5f,  0.5f),
        glm::vec3(-0.5f, -0.5f,  0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),

        glm::vec3(-0.5f,  0.5f, -0.5f),
        glm::vec3(0.5f,  0.5f, -0.5f),
        glm::vec3(0.5f,  0.5f,  0.5f),
        glm::vec3(0.5f,  0.5f,  0.5f),
        glm::vec3(-0.5f,  0.5f,  0.5f),
        glm::vec3(-0.5f,  0.5f, -0.5f)
    };
    std::vector<glm::vec3> cube_normals = {
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),

        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),

        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),

        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),

        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),

        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f) };

    std::vector<glm::vec2> cube_uvs = {
         glm::vec2(0.0f, 0.0f),
         glm::vec2(1.0f, 0.0f),
         glm::vec2(1.0f, 1.0f),
         glm::vec2(1.0f, 1.0f),
         glm::vec2(0.0f, 1.0f),
         glm::vec2(0.0f, 0.0f),

         glm::vec2(0.0f, 0.0f),
         glm::vec2(1.0f, 0.0f),
         glm::vec2(1.0f, 1.0f),
         glm::vec2(1.0f, 1.0f),
         glm::vec2(0.0f, 1.0f),
         glm::vec2(0.0f, 0.0f),

         glm::vec2(1.0f, 0.0f),
         glm::vec2(1.0f, 1.0f),
         glm::vec2(0.0f, 1.0f),
         glm::vec2(0.0f, 1.0f),
         glm::vec2(0.0f, 0.0f),
         glm::vec2(1.0f, 0.0f),

         glm::vec2(1.0f, 0.0f),
         glm::vec2(1.0f, 1.0f),
         glm::vec2(0.0f, 1.0f),
         glm::vec2(0.0f, 1.0f),
         glm::vec2(0.0f, 0.0f),
         glm::vec2(1.0f, 0.0f),

         glm::vec2(0.0f, 1.0f),
         glm::vec2(1.0f, 1.0f),
         glm::vec2(1.0f, 0.0f),
         glm::vec2(1.0f, 0.0f),
         glm::vec2(0.0f, 0.0f),
         glm::vec2(0.0f, 1.0f),

         glm::vec2(0.0f, 1.0f),
         glm::vec2(1.0f, 1.0f),
         glm::vec2(1.0f, 0.0f),
         glm::vec2(1.0f, 0.0f),
         glm::vec2(0.0f, 0.0f),
         glm::vec2(0.0f, 1.0f)
    };


};

