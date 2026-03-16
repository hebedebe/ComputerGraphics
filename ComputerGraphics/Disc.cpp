#include "Disc.h"

#include <utility>

#include "Gizmos.h"

Disc::Disc(const Transform& transform, const float innerRadius, const float outerRadius, const glm::vec4 color, Actor* parent, std::string name)
	:Actor(transform, parent, std::move(name)), innerRadius(innerRadius), outerRadius(outerRadius), color(color)
{
}

void Disc::Draw()
{
	Actor::Draw();

	auto globalTransform = GlobalTransform();
	aie::Gizmos::addRing(VEC3_ZERO, innerRadius, outerRadius, 12, color, &globalTransform.matrix);
}
