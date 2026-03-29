#pragma once

#include <glm/glm.hpp>

#include "Light.h"
#include "Constants.h"
#include "Signal.h"

#define _MAX_LIGHTS 16

class Environment {
	friend class NodeTree;

public:
	void MarkLightingDirty();

public:
	Light sunLight{
		.diffuse = {0.f, 1.f, 0.f},
		.specular = _VEC3_ONE,
		.direction = _VEC3_ONE
	};
	vec3 ambientLight{ .5f, .5f, .5f };
	vec3 backgroundColor{ .25f, .25f, .25f };

	vec3 pointLightPositions[_MAX_LIGHTS];
	vec3 pointLightColours[_MAX_LIGHTS];
	int registeredLights = 0;

public:
	bool lightingDirty = true;
	Signal<> buildLights;

protected:
	void Update();
};