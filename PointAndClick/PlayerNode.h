#pragma once

#include "C:/Users/night/source/repos/hebedebe/ComputerGraphics/ComputerGraphics/Node.h"
#include "PathNode.h"

class PlayerNode :
    public Node
{
public:
    _NODE_DEFAULT_CONSTRUCTOR(PlayerNode)

public:
    void Tick(float delta) override;

public:
    PathNode* currentPathNode = nullptr;
    PathNode::Facing facing = PathNode::Facing::NORTH;
};

