#pragma once

#include <glm/glm.hpp>

#include "Light.h"
#include "Constants.h"

#define _MAX_LIGHTS 16

struct Environment {
	Light sunLight{
		.diffuse = {0.f, 1.f, 0.f},
		.specular = _VEC3_ONE,
		.direction = _VEC3_ONE
	};
	glm::vec3 ambientLight{ .5f, .5f, .5f };
	glm::vec3 backgroundColor{ .25f, .25f, .25f };

	glm::vec3 pointLightPositions[_MAX_LIGHTS];
	glm::vec3 pointLightColours[_MAX_LIGHTS];
	int registeredLights = 0;
};