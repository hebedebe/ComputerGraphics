#include "Transform.h"

#include <format>
#include <glm/glm.hpp>

using namespace glm;

Transform::Transform()
	:m_matrix(mat4(1))
{
	Decompose();
}

Transform::Transform(const mat4& transformMatrix)
	:m_matrix(transformMatrix)
{
	Decompose();
}

Transform::Transform(const vec3 position, const vec3 rotation, const vec3 scale)
	:m_matrix(mat4(1)), m_position(position), m_rotation(rotation), m_scale(scale)
{
	Recompose();
}

void Transform::Recompose()
{
	m_matrix = mat4(1.f);

	m_matrix = scale(m_matrix, m_scale);

	m_matrix = translate(m_matrix, m_position);

	m_matrix = rotate(m_matrix, m_rotation.x, vec3(1, 0, 0));
	m_matrix = rotate(m_matrix, m_rotation.y, vec3(0, 1, 0));
	m_matrix = rotate(m_matrix, m_rotation.z, vec3(0, 0, 1));

}

void Transform::Decompose()
{
	m_position = vec3(m_matrix[3]);

	m_scale.x = length(vec3(m_matrix[0]));
	m_scale.y = length(vec3(m_matrix[1]));
	m_scale.z = length(vec3(m_matrix[2]));

	mat3 rot(
		vec3(m_matrix[0]) / m_scale.x,
		vec3(m_matrix[1]) / m_scale.y,
		vec3(m_matrix[2]) / m_scale.z
	);

	m_rotation.x = atan2(rot[1][2], rot[2][2]);
	m_rotation.y = atan2(-rot[0][2], sqrt(rot[1][2] * rot[1][2] + rot[2][2] * rot[2][2]));
	m_rotation.z = atan2(rot[0][1], rot[0][0]);

	Recompose();
}

void Transform::SetPosition(const vec3 position)
{
	if (position == m_position) return;
	m_position = position; 
	MakeDirty();
}

void Transform::SetRotationRadians(const vec3 rotation)
{
	m_rotation = rotation;
	MakeDirty();
}

void Transform::SetRotationDegrees(const vec3 rotation)
{
	SetRotationRadians(radians(rotation));
}

vec3 Transform::GetRotationDegrees() const
{
	return degrees(m_rotation);
}

void Transform::SetScale(const vec3 scale)
{
	m_scale = scale;    
	MakeDirty();
}

vec3 Transform::GetPosition() const
{
	return m_position;
}

vec3 Transform::GetRotationRadians() const
{
	return m_rotation;
}

vec3 Transform::GetScale() const
{
	return m_scale;
}

void Transform::Move(const vec3 position)
{
	
	SetPosition(m_position + position);
}

void Transform::RotateDegrees(const vec3 rotation)
{
	SetRotationRadians(m_rotation + radians(rotation));
}

void Transform::RotateRadians(const vec3 rotation)
{
	SetRotationRadians(m_rotation + rotation);
}

void Transform::AddScale(const vec3 scale)
{
	SetScale(m_scale + scale);
}

void Transform::SetMatrix(const mat4& matrix)
{
	m_matrix = matrix;
	Decompose();
}

mat4 Transform::GetMatrix()
{
	if (m_dirty)
	{
		Recompose();
		Clean();
	}
	return m_matrix;
}

Transform Transform::operator*(Transform& other)
{
	const Transform result(GetMatrix() * other.GetMatrix());
	return result;
}

std::string Transform::ToString()
{
	vec3 rotationDegrees = degrees(m_rotation);

	return std::format("Position: [{}, {}, {}], Rotation: [{}, {}, {}], Scale: [{}, {}, {}]",
		m_position.x, m_position.y, m_position.z, 
		rotationDegrees.x, rotationDegrees.y, rotationDegrees.z,
		m_scale.x, m_scale.y, m_scale.z);
}

void Transform::MakeDirty()
{
	m_dirty = true;
	dirtied.Emit();
}

void Transform::Clean()
{
	m_dirty = false;
}
