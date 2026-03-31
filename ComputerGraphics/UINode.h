#pragma once
#include "Node.h"

typedef std::function<void(float delta, size_t index)> ui_func;

class UiNode :
    public Node
{
public:
	_NODE_DEFAULT_CONSTRUCTOR(UiNode)

public:
	void Tick(float delta) override;

public:
	void AddContents(const ui_func& func);

protected:
	std::vector<ui_func> m_uiContents;
};

