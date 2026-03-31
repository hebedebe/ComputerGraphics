#pragma once

#include <glm/glm.hpp>

using namespace glm;

struct Particle
{
	vec3 position;
	vec3 velocity;
	vec4 colour;
	float size;
	float lifetime;
	float lifespan;
};

struct ParticleVertex
{
	vec4 position;
	vec4 colour;
};