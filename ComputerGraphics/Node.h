#pragma once

#include <string>
#include <vector>

#include "Transform.h"
#include "Signal.h"

class Node
{
public:
	explicit Node(const Transform& transform, Node* parent = nullptr, std::string name = "Node");
	~Node();

public:
	virtual void Tick(float delta);
	virtual void PreDraw();
	virtual void Draw();

	void Free();
	void QueueFree();

	void RemoveChild(Node* actor);
	void AddChild(Node* actor);

	[[nodiscard]] Transform GlobalTransform();

	template<typename T>
	T* As() { return dynamic_cast<T*>(this); }

public:
	Transform transform;
	Node* parent = nullptr;
	std::vector<Node*> children;
	std::string name;

	bool visible = true;

protected:
	virtual void OnDestroy();
};

