#include "MotionNode.h"


void MotionNode::Tick(const float delta)
{
	Node::Tick(delta);

	if (parent)
	{
		parent->transform.AddScale(scaleMotion * delta);
		parent->transform.Move(translateMotion * delta);
		parent->transform.RotateDegrees(rotateMotion * delta);
	}
}
