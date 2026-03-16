#include "Actor.h"

#include "ComputerGraphicsApp.h"
#include <ranges>
#include <glm/gtc/matrix_transform.hpp>

Actor::Actor(const Transform& transform, Actor* parent, std::string name)
	:transform(transform), parent(parent), name(std::move(name))
{
	if (parent)
		parent->AddChild(this);
	ComputerGraphicsApp::Get()->RegisterBody(this);
}

Actor::~Actor()
{
	for (auto &child : children)
	{
		delete child;
		child = nullptr;
	}
}

void Actor::Tick(float delta)
{
}

void Actor::Draw()
{
}

void Actor::Free()
{
	if (parent)
		parent->RemoveChild(this);
	ComputerGraphicsApp::Get()->RemoveBody(this);
	delete this;
}

void Actor::QueueFree()
{
	ComputerGraphicsApp::Get()->AddToFreeQueue(this);
}

void Actor::RemoveChild(Actor* actor)
{
	actor->parent = nullptr;
	children.erase(std::ranges::find(children, actor));
}

void Actor::AddChild(Actor* actor)
{
	if (actor->parent)
	{
		actor->parent->RemoveChild(actor);
	}

	actor->parent = this;
	children.emplace_back(actor);
}

Transform Actor::GlobalTransform() const
{
	if (not parent) return transform;
	const Transform parentTransform = parent->GlobalTransform();
	Transform tempTransform = glm::mat4(1);
	tempTransform.matrix = glm::translate(tempTransform.matrix, transform.GetPosition());
	tempTransform.matrix = glm::rotate(tempTransform.matrix, transform.GetRotation().x, glm::vec3(1, 0, 0));
	tempTransform.matrix = glm::rotate(tempTransform.matrix, transform.GetRotation().y, glm::vec3(0, 1, 0));
	tempTransform.matrix = glm::rotate(tempTransform.matrix, transform.GetRotation().z, glm::vec3(0,0,1));
	return parentTransform * tempTransform;
}
