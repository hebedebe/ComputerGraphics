#include "MotionNode.h"

#include <utility>

MotionNode::MotionNode(const Transform& transform, Transform motionTransform, Node* parent, std::string name)
	:Node(transform, parent, std::move(name)), motionTransform(std::move(motionTransform))
{
}

void MotionNode::Tick(const float delta)
{
	Node::Tick(delta);

	if (parent)
	{
		parent->transform.Move(motionTransform.GetPosition() * delta);
		parent->transform.RotateDegrees(motionTransform.GetRotationRadians() * delta);
		parent->transform.AddScale(motionTransform.GetScale() * delta);
	}
}
