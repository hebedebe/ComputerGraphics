#include "Node.h"

#include <format>

#include "ComputerGraphicsApp.h"
#include <ranges>
//#include <glm/ext.hpp>

Node::Node(Transform transform, Node* parent, std::string name)
	:transform(transform), parent(parent), name(std::move(name))
{
	if (parent)
		parent->AddChild(this);
	//ComputerGraphicsApp::Get()->GetTree()->QueueRegisterNode(this);
}

Node::~Node()
{
	OnDestroy();

	for (auto &child : children)
	{
		child->parent = nullptr;
		child->Free();
		child = nullptr;
	}
}

void Node::Ready()
{
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

void Node::PostDraw()
{
}

void Node::Free()
{
	if (parent)
		parent->RemoveChild(this);
	m_tree->RemoveNode(this);
	delete this;
}

void Node::QueueFree()
{
	m_tree->AddToFreeQueue(this);
}

void Node::RemoveChild(Node* actor)
{
	actor->parent = nullptr;
	transform.dirtied.Disconnect(actor);
	children.erase(std::ranges::find(children, actor));
}

void Node::AddChild(Node* actor)
{
	if (actor->parent)
	{
		actor->parent->RemoveChild(actor);
	}

	actor->parent = this;
	transform.dirtied.Connect(actor, [actor] {actor->transform.MakeDirty();});
	children.emplace_back(actor);
}

std::string Node::GetUniqueName()
{
	return std::format("{}##{}", name, reinterpret_cast<unsigned long long>(this));
}

Transform Node::GlobalTransform()
{
	if (not parent) return transform;
	Transform parentTransform = parent->GlobalTransform();
	return parentTransform * transform;
}

void Node::OnDestroy()
{
}
