#include "LightNode.h"

#include "ComputerGraphicsApp.h"
#include "Gizmos.h"
#include "imgui.h"

LightNode::LightNode(const Transform& transform, Node* parent, std::string name, const Light& light)
	:Node(transform, parent, std::move(name)), m_lightData(light)
{
	this->transform.dirtied.Connect(this, [this] {m_tree->environment.MarkLightingDirty(); });
}

void LightNode::UpdateLightData()
{
	m_lightData.direction = GlobalTransform().GetRotationRadians();
}

Light LightNode::GetLightData() const
{
	return m_lightData;
}

void LightNode::Tick(float delta)
{
	Node::Tick(delta);

	ImGui::Begin(GetUniqueName().c_str());

	vec3 position = _VEC3_ZERO;

	ImGui::SliderFloat3("Position", value_ptr(position), -20, 20);
	ImGui::ColorEdit3("Colour", value_ptr(m_lightData.diffuse));
	ImGui::DragFloat("Intensity", &m_lightData.intensity);
	ImGui::Checkbox("Render gizmo", &m_debug);

	transform.Move(position * delta);

	ImGui::End();
}

void LightNode::Draw()
{
	Node::Draw();

	if (m_debug)
		aie::Gizmos::addSphere(GlobalTransform().GetPosition(), 0.1f, 12, 12, glm::vec4(m_lightData.diffuse, 1));
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

	m_tree->environment.pointLightColours[index] = m_lightData.diffuse * m_lightData.intensity;
	m_tree->environment.pointLightPositions[index] = GlobalTransform().GetPosition();

	environment.registeredLights++;
}
