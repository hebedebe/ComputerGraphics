#include "PathNode.h"

#include "Gizmos.h"
#include "../ComputerGraphics/Filters.h"

void PathNode::Draw()
{
	Node::Draw();

	const auto matrix = GlobalTransform().GetMatrix();
	aie::Gizmos::addSphere(_VEC3_ZERO, 0.1f, 12, 12, _YELLOW, &matrix);

	const Transform globalTransform = GlobalTransform();

	for (const auto& connection : connections | 
		std::ranges::views::values | _FILTER_NULLPTR)
	{
		aie::Gizmos::addLine(globalTransform.GetPosition(), connection->GlobalTransform().GetPosition(), _YELLOW);
	}
}

void PathNode::Connect(const Facing& facing, PathNode* connection)
{
	connections[facing] = connection;

	connection->connections[(Facing)((facing+2)%4)] = this;
}

void PathNode::Interact(const Facing& facing)
{
	if (interactions[facing].active) interactions[facing].action();
}
