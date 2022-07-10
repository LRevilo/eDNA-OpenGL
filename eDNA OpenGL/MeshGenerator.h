#pragma once
#include <vector>
#include "glm.h"
class MeshGenerator
{

private:

public:

	MeshGenerator();
	~MeshGenerator();



	void Reset(struct MeshComponent& MC);
	void Plane(struct MeshComponent& MC, int Size = 2);
	void Cylinder(struct MeshComponent& MC, int SizeX = 2, int SizeY = 2);
	void Cube(struct MeshComponent& MC);

private:

    std::vector<glm::vec3> cube_vertices = {
        //bottom face
        glm::vec3(0, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(1, 1, 0),

        //top face
        glm::vec3(0, 0, 1),
        glm::vec3(1, 0, 1),
        glm::vec3(0, 1, 1),
        glm::vec3(1, 1, 1),

        //facing -y
        glm::vec3(0, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(0, 0, 1),
        glm::vec3(1, 0, 1),

        //facing +y
        glm::vec3(0, 1, 0),
        glm::vec3(1, 1, 0),
        glm::vec3(0, 1, 1),
        glm::vec3(1, 1, 1),

        //facing -x
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 0, 1),
        glm::vec3(0, 1, 1),
        
        //facing +x
        glm::vec3(1, 0, 0),
        glm::vec3(1, 1, 0),
        glm::vec3(1, 0, 1),
        glm::vec3(1, 1, 1),


    };
    std::vector<glm::vec3> cube_normals = {
        //bottom face
        glm::vec3(0, 0, -1),
        glm::vec3(0, 0, -1),
        glm::vec3(0, 0, -1),
        glm::vec3(0, 0, -1),
        //top face
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),

        //facing -y
        glm::vec3(0, -1, 0),
        glm::vec3(0, -1, 0),
        glm::vec3(0, -1, 0),
        glm::vec3(0, -1, 0),
        
        //facing +y
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        
        //facing -x
        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0),
        
        //facing +x
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0)
 };
    std::vector<glm::vec2> cube_uvs = {
        //bottom face
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
        //top face
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),

        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
        
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
        
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
        
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
    };
    std::vector<int> cube_indicies = {
        0,1,2,2,1,3,
        4,5,6,6,5,7,
        8,9,10,10,9,11,
        12,13,14,14,13,15,
        16,17,18,18,17,19,
        20,21,22,22,21,23
    };



};

