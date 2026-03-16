#pragma once
#include "Constants.h"

class Transform
{
public:
	Transform(); //Defaults to identity
	Transform(const glm::mat4& transformMatrix);
	Transform(const glm::vec3 position, const glm::vec3 rotation = VEC3_ZERO, const glm::vec3 scale = VEC3_ONE);

public:
	void SetPosition(glm::vec3 position);
	void SetRotation(glm::vec3 rotation);
	void SetScale(glm::vec3 scale);

	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;

	static Transform Identity();

public:
	Transform operator* (const Transform& other) const;

public:
	glm::mat4 matrix;
};

