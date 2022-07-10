#pragma once
#include "glm.h"
struct PointLightComponent
{
	glm::vec4 Color;
	glm::dvec3 Position;
	float Falloff;

	PointLightComponent() = default;
	PointLightComponent(const PointLightComponent&) = default;
	PointLightComponent(glm::vec4 color, glm::dvec3 position, float falloff)
		: Color(color), Position(position), Falloff(falloff) {}



};