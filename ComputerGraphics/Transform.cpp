#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

Transform::Transform()
	:matrix(glm::mat4(1))
{
}

Transform::Transform(const glm::mat4& transformMatrix)
	:matrix(transformMatrix)
{
}

Transform::Transform(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale)
	:matrix(glm::mat4(1))
{
	SetPosition(position);
	SetRotation(rotation);
	SetScale(scale);
}

void Transform::SetPosition(const glm::vec3 position)
{
	matrix[3][0] = position.x;
	matrix[3][1] = position.y;
	matrix[3][2] = position.z;
}

void Transform::SetRotation(const glm::vec3 rotation)
{
	matrix[0][3] = rotation.x;
	matrix[1][3] = rotation.y;
	matrix[2][3] = rotation.z;
}

void Transform::SetScale(const glm::vec3 scale)
{
	matrix[0][0] = scale.x;
	matrix[1][1] = scale.y;
	matrix[2][2] = scale.z;
}

glm::vec3 Transform::GetPosition() const
{
	return {
		matrix[3][0],
		matrix[3][1],
		matrix[3][2]
	};
}

glm::vec3 Transform::GetRotation() const
{
	return {
		matrix[0][3],
		matrix[1][3],
		matrix[2][3]
	};
}

glm::vec3 Transform::GetScale() const
{
	return {
		matrix[0][0],
		matrix[1][1],
		matrix[2][2]
	};
}

void Transform::Move(const glm::vec3 position)
{
	SetPosition(GetPosition() + position);
}

void Transform::Rotate(const glm::vec3 rotation)
{
	matrix = glm::rotate(matrix, rotation.x, glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, rotation.y, glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, rotation.z, glm::vec3(0,0,1));
}

void Transform::AddScale(const glm::vec3 scale)
{
	SetScale(GetScale() + scale);
}

Transform Transform::Identity()
{
	return {};
}

Transform Transform::operator*(const Transform& other) const
{
	return { matrix * other.matrix };
}
