#pragma once
#include "glm.h"
#include "entt/entt.hpp"

struct TransformComponent
{
	glm::dvec3 Translation = { 0.0, 0.0, 0.0 };
	glm::vec3 Rotation = { 0.f, 0.f, 0.f };
	glm::vec3 Scale = { 1.f, 1.f, 1.f };

	TransformComponent() = default;
	TransformComponent(const TransformComponent&) = default;
	TransformComponent(const glm::dvec3& translation)
		: Translation(translation) {}


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