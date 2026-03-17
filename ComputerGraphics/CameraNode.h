#pragma once
#include "Node.h"

class CameraNode :
    public Node
{
public:
    CameraNode();

public:
    bool active = true;
};

