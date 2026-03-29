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
		constexpr float moveSpeed = 3.f;
		constexpr float rotationSpeed = 20.f;

		glm::vec3 position(0, 0, 0);
		glm::vec3 rotation(0, 0, 0);

		ImGui::Begin("Camera controls");
		ImGui::SliderFloat3("Position", value_ptr(position), -moveSpeed, moveSpeed);
		ImGui::SliderFloat3("Rotation", value_ptr(rotation), -rotationSpeed, rotationSpeed);

		ImGui::SliderFloat("Fov", &fov, 1, 179);
		ImGui::SliderFloat("Width", &width, 1, 100);
		ImGui::SliderFloat("Height", &height, 1, 100);

		ImGui::TextWrapped("%s", transform.ToString().c_str());
		ImGui::End();

		transform.RotateDegrees(rotation * delta);
		transform.Move(position * delta);
	}
}

void CameraNode::PreDraw()
{
	Node::PreDraw();

	assert(m_active); // If it's not active something is wrong

	const auto app = ComputerGraphicsApp::Get();
	m_tree->SetActiveCamera(this);
	app->SetProjectionMatrix(GetProjectionMatrix());
	app->SetViewMatrix(GetViewMatrix());
}

glm::mat4 CameraNode::GetViewMatrix()
{
	return GlobalTransform().GetMatrix();
}

glm::mat4 CameraNode::GetProjectionMatrix() const
{
	switch (m_projectionMode)
	{
		case ProjectionMode::ORTHOGRAPHIC:
			{
				const float halfWidth = width / 2.f;
				const float halfHeight = height / 2.f;
				return glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, nearClip, farClip);
			}
			
		case ProjectionMode::PERSPECTIVE:
			return glm::perspectiveFov(glm::radians(fov), width, height, nearClip, farClip);
	}

	throw std::exception("Camera has invalid projection mode.");
}

void CameraNode::SetActive(const bool active)
{
	if (active == m_active) return;
	m_active = active;
	if (active)
	{
		m_tree->RegisterPreDraw(this);
	}
	else
	{
		m_tree->RemovePreDraw(this);
	}
}

void CameraNode::OnDestroy()
{
	Node::OnDestroy();

	if (m_active) m_tree->RemovePreDraw(this);
}
