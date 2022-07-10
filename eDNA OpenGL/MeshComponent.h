#pragma once
#include "glm.h"
#include <vector>

#define MAX_BONE_INFLUENCE 4

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 UV;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    float m_Weights[MAX_BONE_INFLUENCE];
};

struct MeshComponent
{
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    unsigned int Material{ 0 };

    glm::dvec3 Translation { 0.0, 0.0, 0.0 };
    glm::vec3 Rotation { 0.f, 0.f, 0.f };
    glm::vec3 Scale { 1.f, 1.f, 1.f };

	MeshComponent() = default;
	MeshComponent(const MeshComponent&) = default;
	MeshComponent(const std::vector<Vertex> vertices, const std::vector<unsigned int> indices, const unsigned int material)
		: Vertices(vertices), Indices(indices), Material(material) {}

    glm::mat4 GetTransform(glm::dvec3 translation = { 0.0, 0.0, 0.0 }) const
    {
        glm::mat4 matrix = glm::mat4(1.0f);
        matrix = glm::translate(matrix, (glm::vec3)(Translation - translation));
        matrix = glm::rotate(matrix, Rotation.z, glm::vec3(0, 0, 1));
        matrix = glm::rotate(matrix, Rotation.y, glm::vec3(0, 1, 0));
        matrix = glm::rotate(matrix, Rotation.x, glm::vec3(1, 0, 0));
        matrix = glm::scale(matrix, Scale);
        return matrix;
    }

};