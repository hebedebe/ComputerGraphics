#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Transform.h"

class Actor
{
public:
	Actor(const Transform& transform, Actor* parent = nullptr, std::string name = "Actor");
	virtual ~Actor();

public:
	virtual void Tick(float delta);
	virtual void Draw();

	void Free();
	void QueueFree();

	void RemoveChild(Actor* actor);
	void AddChild(Actor* actor);

	Transform GlobalTransform() const;

public:
	Transform transform;
	Actor* parent = nullptr;
	std::vector<Actor*> children;
	std::string name;

	bool visible = true;
};

