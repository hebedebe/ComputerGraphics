#include "Transform.h"

#include <format>
#include <glm/gtc/matrix_transform.hpp>

Transform::Transform()
	:m_matrix(glm::mat4(1))
{
	Decompose();
}

Transform::Transform(const glm::mat4& transformMatrix)
	:m_matrix(transformMatrix)
{
	Decompose();
}

Transform::Transform(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale)
	:m_matrix(glm::mat4(1)), m_position(position), m_rotation(rotation), m_scale(scale)
{
	Recompose();
}

void Transform::Recompose()
{
	m_matrix = glm::mat4(1.f);

	m_matrix = glm::scale(m_matrix, m_scale);


	m_matrix = glm::rotate(m_matrix, m_rotation.x, glm::vec3(1, 0, 0));
	m_matrix = glm::rotate(m_matrix, m_rotation.y, glm::vec3(0, 1, 0));
	m_matrix = glm::rotate(m_matrix, m_rotation.z, glm::vec3(0, 0, 1));


	m_matrix = glm::translate(m_matrix, m_position);
}

void Transform::Decompose()
{
	m_position = glm::vec3(m_matrix[3]);

	m_scale.x = glm::length(glm::vec3(m_matrix[0]));
	m_scale.y = glm::length(glm::vec3(m_matrix[1]));
	m_scale.z = glm::length(glm::vec3(m_matrix[2]));

	glm::mat3 rot(
		glm::vec3(m_matrix[0]) / m_scale.x,
		glm::vec3(m_matrix[1]) / m_scale.y,
		glm::vec3(m_matrix[2]) / m_scale.z
	);

	m_rotation.x = atan2(rot[1][2], rot[2][2]);
	m_rotation.y = atan2(-rot[0][2], glm::sqrt(rot[1][2] * rot[1][2] + rot[2][2] * rot[2][2]));
	m_rotation.z = atan2(rot[0][1], rot[0][0]);

	Recompose();
}

void Transform::SetPosition(const glm::vec3 position)
{
	m_position = position; 
	Recompose();
}

void Transform::SetRotationRadians(const glm::vec3 rotation)
{
	m_rotation = rotation;
	Recompose();
}

void Transform::SetRotationDegrees(const glm::vec3 rotation)
{
	SetRotationRadians(glm::radians(rotation));
}

glm::vec3 Transform::GetRotationDegrees() const
{
	return glm::degrees(m_rotation);
}

void Transform::SetScale(const glm::vec3 scale)
{
	m_scale = scale;    
	Recompose();
}

glm::vec3 Transform::GetPosition() const
{
	return m_position;
}

glm::vec3 Transform::GetRotationRadians() const
{
	return m_rotation;
}

glm::vec3 Transform::GetScale()    const
{
	return m_scale;
}

void Transform::Move(const glm::vec3 position)
{
	SetPosition(m_position + position);
}

void Transform::RotateDegrees(const glm::vec3 rotation)
{
	SetRotationRadians(m_rotation + glm::radians(rotation));
}

void Transform::RotateRadians(const glm::vec3 rotation)
{
	SetRotationRadians(m_rotation + rotation);
}

void Transform::AddScale(const glm::vec3 scale)
{
	SetScale(m_scale + scale);
}

void Transform::SetMatrix(const glm::mat4& matrix)
{
	m_matrix = matrix;
	Decompose();
}

glm::mat4 Transform::GetMatrix() const
{
	return m_matrix;
}

Transform Transform::operator*(const Transform& other) const
{
	const Transform result(m_matrix * other.m_matrix);
	return result;
}

std::string Transform::ToString()
{
	glm::vec3 rotationDegrees = glm::degrees(m_rotation);

	return std::format("Position: [{}, {}, {}], Rotation: [{}, {}, {}], Scale: [{}, {}, {}]",
		m_position.x, m_position.y, m_position.z, 
		rotationDegrees.x, rotationDegrees.y, rotationDegrees.z,
		m_scale.x, m_scale.y, m_scale.z);
}
