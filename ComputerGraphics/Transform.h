#pragma once
#include <glm/glm.hpp>
#include "Constants.h"

class Transform
{
public:
	Transform(); //Defaults to identity
	Transform(const glm::mat4& transformMatrix);
	Transform(const glm::vec3 position, const glm::vec3 rotation = _VEC3_ZERO, const glm::vec3 scale = _VEC3_ONE);

public:
	void SetPosition(glm::vec3 position);
	void SetRotation(glm::vec3 rotation);
	void SetScale(glm::vec3 scale);

	[[nodiscard]] glm::vec3 GetPosition() const;
	[[nodiscard]] glm::vec3 GetRotation() const;
	[[nodiscard]] glm::vec3 GetScale() const;

	void Move(glm::vec3 position);
	void Rotate(glm::vec3 rotation);
	void AddScale(glm::vec3 scale);

	static Transform Identity();

public:
	Transform operator* (const Transform& other) const;

public:
	glm::mat4 matrix;
};

