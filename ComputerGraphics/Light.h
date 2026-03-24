#pragma once

#include <glm/glm.hpp>

using namespace glm;

struct Light
{
    vec3 diffuse;
    vec3 specular;
    vec3 direction;
    float intensity = 10.f;
};