#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Constants.h"
#include "Signal.h"

class Transform
{
public:
	Transform(); //Defaults to identity
	Transform(const glm::mat4& transformMatrix);
	Transform(const glm::vec3 position, const glm::vec3 rotation = _VEC3_ZERO, const glm::vec3 scale = _VEC3_ONE);

public:
	void Recompose();
	void Decompose();

	void SetPosition(glm::vec3 position);
	void SetRotationRadians(glm::vec3 rotation);
	void SetRotationDegrees(glm::vec3 rotation);
	void SetScale(glm::vec3 scale);

	[[nodiscard]] glm::vec3 GetPosition() const;
	[[nodiscard]] glm::vec3 GetRotationRadians() const;
	[[nodiscard]] glm::vec3 GetRotationDegrees() const;
	[[nodiscard]] glm::vec3 GetScale() const;

	void Move(const glm::vec3 position);
	void RotateDegrees(const glm::vec3 rotation);
	void RotateRadians(const glm::vec3 rotation);
	void AddScale(const glm::vec3 scale);

	void SetMatrix(const glm::mat4& matrix);
	glm::mat4 GetMatrix();

	void Reset(); //Resets matrix to identity

public:
	static glm::mat4 Identity();

public:
	Transform operator* (Transform& other);

	std::string ToString();

	void MakeDirty();
	void Clean();

public:
	Signal<> dirtied;

private:
	glm::mat4 m_matrix;

	glm::vec3 m_position;
	glm::vec3 m_rotation; // In radians
	glm::vec3 m_scale;

	bool m_dirty; // Only recompose/decompose if dirty
};

