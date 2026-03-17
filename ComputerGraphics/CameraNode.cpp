#include "CameraNode.h"

#include <utility>

#include "ComputerGraphicsApp.h"
#include "imgui.h"

CameraNode::CameraNode(const Transform& transform, Node* parent, std::string name)
	:Node(transform, parent, std::move(name))
{
}

void CameraNode::Tick(const float delta)
{
	Node::Tick(delta);

	if (m_active)
	{
		constexpr float moveSpeed = 10.f;
		constexpr float rotationSpeed = 10.f;

		glm::vec3 position(0, 0, 0);
		glm::vec3 rotation(0, 0, 0);

		ImGui::Begin("Camera controls");
		ImGui::SliderFloat3("Position", value_ptr(position), -moveSpeed, moveSpeed);
		ImGui::SliderFloat3("Rotation", value_ptr(rotation), -rotationSpeed, rotationSpeed);
		ImGui::End();

		transform.Rotate(rotation * delta);
		transform.Move(position * delta);
	}
}

void CameraNode::PreDraw()
{
	Node::PreDraw();

	assert(m_active); // If it's not active something is wrong

	const auto app = ComputerGraphicsApp::Get();
	app->SetProjectionMatrix(GetProjectionMatrix());
	app->SetViewMatrix(GetViewMatrix());
}

glm::mat4 CameraNode::GetViewMatrix() const
{
	return GlobalTransform().matrix;
}

glm::mat4 CameraNode::GetProjectionMatrix() const
{
	return glm::perspectiveFov(glm::radians(fov), width, height, nearClip, farClip);
}

void CameraNode::SetActive(const bool active)
{
	if (active == m_active) return;
	m_active = active;
	if (active)
	{
		ComputerGraphicsApp::Get()->RegisterPreDraw(this);
	}
	else
	{
		ComputerGraphicsApp::Get()->RemovePreDraw(this);
	}
}

void CameraNode::OnDestroy()
{
	Node::OnDestroy();

	if (m_active) ComputerGraphicsApp::Get()->RemovePreDraw(this);
}
