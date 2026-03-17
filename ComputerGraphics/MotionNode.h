#pragma once
#include "Node.h"
class MotionNode :
    public Node
{
public:
    MotionNode(const Transform& transform, const Transform& motionTransform, Node* parent = nullptr, std::string name = "MotionNode");

public:
    void Tick(float delta) override;

public:
    Transform motionTransform;
};

