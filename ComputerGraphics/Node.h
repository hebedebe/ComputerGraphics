#pragma once

#include <string>
#include <vector>

#include "Transform.h"

class Node
{
public:
	Node(const Transform& transform, Node* parent = nullptr, std::string name = "Node");
	virtual ~Node();

public:
	virtual void Tick(float delta);
	virtual void Draw();

	void Free();
	void QueueFree();

	void RemoveChild(Node* actor);
	void AddChild(Node* actor);

	Transform GlobalTransform() const;

	template<typename T>
	T* As() { return dynamic_cast<T*>(this); }

public:
	Transform transform;
	Node* parent = nullptr;
	std::vector<Node*> children;
	std::string name;

	bool visible = true;

protected:
	void OnDestroy();
};

