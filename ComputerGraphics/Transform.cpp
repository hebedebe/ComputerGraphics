#include "Transform.h"

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

Transform Transform::Identity()
{
	return Transform();
}

Transform Transform::operator*(const Transform& other) const
{
	return { matrix * other.matrix };
}
