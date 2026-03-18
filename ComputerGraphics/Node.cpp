#include "Node.h"

#include "ComputerGraphicsApp.h"
#include <ranges>
//#include <glm/ext.hpp>

Node::Node(const Transform& transform, Node* parent, std::string name)
	:transform(transform), parent(parent), name(std::move(name))
{
	if (parent)
		parent->AddChild(this);
	ComputerGraphicsApp::Get()->RegisterNode(this);
}

Node::~Node()
{
	OnDestroy();

	for (auto &child : children)
	{
		delete child;
		child = nullptr;
	}
}

void Node::Tick(float delta)
{
}

void Node::PreDraw()
{
}

void Node::Draw()
{
}

void Node::Free()
{
	if (parent)
		parent->RemoveChild(this);
	ComputerGraphicsApp::Get()->RemoveNode(this);
	delete this;
}

void Node::QueueFree()
{
	ComputerGraphicsApp::Get()->AddToFreeQueue(this);
}

void Node::RemoveChild(Node* actor)
{
	actor->parent = nullptr;
	children.erase(std::ranges::find(children, actor));
}

void Node::AddChild(Node* actor)
{
	if (actor->parent)
	{
		actor->parent->RemoveChild(actor);
	}

	actor->parent = this;
	children.emplace_back(actor);
}

Transform Node::GlobalTransform() const
{
	if (not parent) return transform;
	const Transform parentTransform = parent->GlobalTransform();
	return parentTransform * transform;
}

void Node::OnDestroy()
{
}
