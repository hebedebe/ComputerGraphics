#include "LightNode.h"

LightNode::LightNode(const Transform& transform, Node* parent, std::string name, Light light)
	:Node(transform, parent, std::move(name)), m_lightData(light)
{

}

void LightNode::UpdateLightData()
{
	m_lightData.direction = GlobalTransform().GetRotationRadians();
}

LightNode::Light LightNode::GetLightData() const
{
	return m_lightData;
}
