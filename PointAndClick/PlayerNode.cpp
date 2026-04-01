#include "PlayerNode.h"

#include "Input.h"
#include "MainMenuLoader.h"

void PlayerNode::Tick(float delta)
{
	Node::Tick(delta);

	aie::Input* input = aie::Input::getInstance();

	if (const int inputDirection = input->wasKeyPressed(aie::INPUT_KEY_RIGHT) - input->wasKeyPressed(aie::INPUT_KEY_LEFT))
		facing = (PathNode::Facing)(((int)facing + inputDirection + 4) % 4);

	const float targetYaw = (float)facing * -90.f;
	const vec3 currentRotation = transform.GetRotationDegrees();

	float yawDiff = targetYaw - currentRotation.y;

	while (yawDiff < -180.0f) yawDiff += 360.0f;
	while (yawDiff >= 180.0f) yawDiff -= 360.0f;

	vec3 interpolatedRotation = currentRotation;
	interpolatedRotation.y += yawDiff * delta * 10.f;

	transform.SetRotationDegrees(interpolatedRotation);

	const vec3 targetPosition = currentPathNode->GlobalTransform().GetPosition();
	const vec3 currentPosition = GlobalTransform().GetPosition();

	const vec3 interpolatedPosition = currentPosition + (targetPosition - currentPosition) * delta * 10.f;

	transform.SetPosition(interpolatedPosition);


	if (input->wasKeyPressed(aie::INPUT_KEY_UP))
	{
		if (currentPathNode)
		{
			if (const auto connection = currentPathNode->GetConnection(facing))
				currentPathNode = connection;
		}
	}
	
	if (input->wasKeyPressed(aie::INPUT_KEY_DOWN))
	{
		if (currentPathNode)
		{
			if (const auto connection = currentPathNode->GetConnection((PathNode::Facing)((facing+2)%4)))
				currentPathNode = connection;
		}
	}

	if (input->wasKeyPressed(aie::INPUT_KEY_C))
	{
		if (currentPathNode)
		{
			if (currentPathNode->HasInteraction(facing))
				currentPathNode->Interact(facing);
		}
	}
}
