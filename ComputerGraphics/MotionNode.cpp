#include "MotionNode.h"

#include <utility>

MotionNode::MotionNode(const Transform& transform, const Transform& motionTransform, Node* parent, std::string name)
	:Node(transform, parent, std::move(name)), motionTransform(motionTransform)
{
}

void MotionNode::Tick(const float delta)
{
	Node::Tick(delta);

	if (parent)
	{
		parent->transform.Move(motionTransform.GetPosition() * delta);
		parent->transform.Rotate(motionTransform.GetRotation() * delta);
		parent->transform.AddScale(motionTransform.GetScale() * delta);
	}
}
