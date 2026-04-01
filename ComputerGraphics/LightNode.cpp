#include "LightNode.h"

#include "ComputerGraphicsApp.h"
#include "Gizmos.h"
#include "imgui.h"

LightNode::LightNode(const Transform& transform, Node* parent, std::string name, const Light& light)
	:Node(transform, parent, std::move(name)), lightData(light)
{
}

void LightNode::UpdateLightData()
{
	lightData.direction = GlobalTransform().GetRotationRadians();
}

Light LightNode::GetLightData() const
{
	return lightData;
}

void LightNode::Ready()
{
	Node::Ready();
	transform.dirtied.Connect(m_tree, [this] {this->m_tree->environment.MarkLightingDirty(); });
	m_tree->environment.buildLights.Connect(this, [this] {RebuildLight(); });
}

void LightNode::Tick(float delta)
{
	Node::Tick(delta);

	_IF_NOT_DEBUG return;

	ImGui::Begin(GetUniqueName().c_str());

	vec3 position = _VEC3_ZERO;

	ImGui::SliderFloat3("Position", value_ptr(position), -20, 20);
	ImGui::ColorEdit3("Colour", value_ptr(lightData.diffuse));
	ImGui::DragFloat("Intensity", &lightData.intensity);
	ImGui::Checkbox("Render gizmo", &m_debug);

	transform.Move(position * delta);

	ImGui::End();
}

void LightNode::Draw()
{
	Node::Draw();

	if (m_debug)
		aie::Gizmos::addSphere(GlobalTransform().GetPosition(), 0.03f * lightData.intensity,
			12, 12, glm::vec4(lightData.diffuse, 1));
}

void LightNode::OnDestroy()
{
	Node::OnDestroy();

	m_tree->environment.buildLights.Disconnect(this);
}

void LightNode::RebuildLight()
{
	auto& environment = m_tree->environment;
	const int& index = environment.registeredLights;

	environment.pointLightColours[index] = lightData.diffuse * lightData.intensity;
	environment.pointLightPositions[index] = GlobalTransform().GetPosition();

	environment.registeredLights++;
}
