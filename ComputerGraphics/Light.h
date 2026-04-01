#pragma once

#include <glm/glm.hpp>

#include "Constants.h"

using namespace glm;

struct Light
{
    vec3 diffuse = _VEC3_ONE;
    vec3 specular = _VEC3_ONE;
    vec3 direction = _VEC3_ZERO;
    float intensity = 20.f;
};