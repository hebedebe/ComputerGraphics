#pragma once

#include "C:/Users/night/source/repos/hebedebe/ComputerGraphics/ComputerGraphics/Node.h"

class PathNode :
    public Node
{
public:
    enum Facing : uint8
    {
	    NORTH,
        EAST,
        SOUTH,
        WEST
    };

    struct Interaction
    {
        bool active = false;
        std::string description;
		std::function<void()> action;
    };

public:
    _NODE_DEFAULT_CONSTRUCTOR(PathNode)

public:
    void Draw() override;

public:
    void Connect(const Facing& facing, PathNode* connection);
	PathNode* GetConnection(const Facing& facing) { return connections[facing]; }

	Interaction GetInteraction(const Facing& facing) { return interactions[facing]; }
    void Interact(const Facing& facing);
	bool HasInteraction(const Facing& facing) { return interactions[facing].active; }

public:
    std::map<Facing, PathNode*> connections;
	std::map<Facing, Interaction> interactions;
};

