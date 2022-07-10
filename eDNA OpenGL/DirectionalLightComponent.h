#pragma once
#include "glm.h"
struct DirectionalLightComponent
{
	glm::vec4 Color;
	glm::vec3 Direction;

	DirectionalLightComponent() = default;
	DirectionalLightComponent(const DirectionalLightComponent&) = default;
	DirectionalLightComponent(glm::vec4 color, glm::vec3 direction)
		: Color(color), Direction(direction) {}

};