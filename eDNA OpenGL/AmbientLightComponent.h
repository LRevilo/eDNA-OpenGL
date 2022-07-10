#pragma once
#include "glm.h"

struct AmbientLightComponent
{
	glm::vec4 Color;

	AmbientLightComponent() = default;
	AmbientLightComponent(const AmbientLightComponent&) = default;
	AmbientLightComponent(glm::vec4 color)
		: Color(color){}

};