#pragma once

#include <string>
#include <vector>

#include "NodeTree.h"
#include "Transform.h"
#include "Signal.h"

class NodeTree;

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

	std::string GetUniqueName();

	[[nodiscard]] Transform GlobalTransform();

	template<typename T>
	T* As() { return dynamic_cast<T*>(this); }

	void SetTree(NodeTree* tree) { m_tree = tree; }
	NodeTree* GetTree() const { return m_tree; }

public:
	Transform transform;
	Node* parent = nullptr;
	std::vector<Node*> children;
	std::string name;

	bool visible = true;

protected:
	virtual void OnDestroy();

protected:
	NodeTree* m_tree;
};

