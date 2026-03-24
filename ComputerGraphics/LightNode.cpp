#include "LightNode.h"

#include "ComputerGraphicsApp.h"
#include "Gizmos.h"

LightNode::LightNode(const Transform& transform, Node* parent, std::string name, const Light& light)
	:Node(transform, parent, std::move(name)), m_lightData(light)
{
	auto app = ComputerGraphicsApp::Get();
	app->MarkLightingDirty();
	app->buildLights.Connect(this, [this] {this->RebuildLight(); });

	this->transform.dirtied.Connect(this, [app] {app->MarkLightingDirty(); });
}

void LightNode::UpdateLightData()
{
	m_lightData.direction = GlobalTransform().GetRotationRadians();
}

Light LightNode::GetLightData() const
{
	return m_lightData;
}

void LightNode::Draw()
{
	Node::Draw();
	aie::Gizmos::addSphere(GlobalTransform().GetPosition(), 0.1f, 12, 12, glm::vec4(m_lightData.diffuse, 1));
}

void LightNode::OnDestroy()
{
	Node::OnDestroy();

	const auto app = ComputerGraphicsApp::Get();
	app->buildLights.Disconnect(this);
}

void LightNode::RebuildLight()
{
	const auto app = ComputerGraphicsApp::Get();

	auto& environment = app->environment;
	const int& index = environment.registeredLights;

	app->environment.pointLightColours[index] = GetLightData().diffuse * GetLightData().intensity;
	app->environment.pointLightPositions[index] = GlobalTransform().GetPosition();

	printf("Rebuilt light at index %d", index);

	environment.registeredLights++;

}
