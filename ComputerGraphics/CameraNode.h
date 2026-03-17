#pragma once
#include "Node.h"
class CameraNode :
    public Node
{
public:
    CameraNode();

public:
    bool active = true;

private:
    float m_theta;
    float m_phi;
};

