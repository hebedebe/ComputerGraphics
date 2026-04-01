#include "CameraNode.h"

#include <utility>

#include "ComputerGraphicsApp.h"
#include "imgui.h"

CameraNode::CameraNode(const Transform& transform, Node* parent, std::string name)
	:Node(transform, parent, std::move(name))
{
	CalculateAspectRatio();
}

void CameraNode::Ready()
{
	Node::Ready();
	if (m_active != m_desiredActive)
	{
		m_active = m_desiredActive;
		if (m_active)
		{
			m_tree->RegisterPreDraw(this);
			const auto app = ComputerGraphicsApp::Get();
			m_tree->SetActiveCamera(this);
			app->SetProjectionMatrix(GetProjectionMatrix());
			app->SetViewMatrix(GetViewMatrix());
		}
	}
}

void CameraNode::Tick(const float delta)
{
	Node::Tick(delta);

	if (m_active != m_desiredActive)
	{
		m_active = m_desiredActive;
		if (m_active)
		{
			m_tree->RegisterPreDraw(this);
		}
		else
		{
			m_tree->RemovePreDraw(this);
			return;
		}
	}

	_IF_NOT_DEBUG return;

	if (m_active)
	{
		constexpr float moveSpeed = 3.f;
		constexpr float rotationSpeed = 20.f;

		vec3 position(0, 0, 0);
		vec3 rotation(0, 0, 0);

		ImGui::Begin("Camera controls");
		ImGui::SliderFloat3("Position", value_ptr(position), -moveSpeed, moveSpeed);
		ImGui::SliderFloat3("Rotation", value_ptr(rotation), -rotationSpeed, rotationSpeed);

		if (ImGui::Button("Reset transform"))
			transform.Reset();

		ImGui::SliderFloat("Fov", &fov, 1, 179);

		ImGui::SliderFloat("Width", &width, 1, 100);
		ImGui::SliderFloat("Height", &height, 1, 100);
		if (ImGui::Button("Recalculate aspect ratio"))
			CalculateAspectRatio();
		if (!IsValidAspectRatio())
			ImGui::TextColored(_RED, "Aspect ratio is invalid! Recalculate it or set it manually.");

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

	if (renderTarget)
	{
		renderTarget->bind();
		
		m_tree->Draw();

		renderTarget->unbind();
	} else
	{
		m_tree->Draw();
	}

}

glm::mat4 CameraNode::GetViewMatrix()
{
	return inverse(GlobalTransform().GetMatrix());
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

void CameraNode::CalculateAspectRatio()
{
	const auto app = ComputerGraphicsApp::Get();

	width = (float)app->GetWindowWidth();
	height = (float)app->GetWindowHeight();
}

bool CameraNode::IsValidAspectRatio() const
{
	const auto app = ComputerGraphicsApp::Get();
	
	return
		width == app->GetWindowWidth() &&
		height == app->GetWindowHeight();
}

void CameraNode::SetActive(const bool active)
{
	m_desiredActive = active;
}

void CameraNode::InitRenderTarget()
{
	const auto app = ComputerGraphicsApp::Get();
	renderTarget = new aie::RenderTarget;
	if (!renderTarget->initialise(1, app->GetWindowWidth(), app->GetWindowHeight()))
	{
		printf("Render target error!\n");
	}
}

void CameraNode::OnDestroy()
{
	Node::OnDestroy();

	delete renderTarget;

	if (m_active) m_tree->RemovePreDraw(this);
}
