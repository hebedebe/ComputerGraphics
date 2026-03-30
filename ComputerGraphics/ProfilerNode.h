#pragma once
#include "Node.h"

class ProfilerNode: public Node
{
public:
	ProfilerNode();

public:
	void Tick(float delta) override;
};

