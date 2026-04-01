#pragma once
#include "Node.h"
class MotionNode :
    public Node
{
public:
    _NODE_DEFAULT_CONSTRUCTOR(MotionNode);

public:
    void Tick(float delta) override;

public:
    vec3 translateMotion = _VEC3_ZERO;
	vec3 rotateMotion = _VEC3_ZERO;
    vec3 scaleMotion = _VEC3_ZERO;
};

