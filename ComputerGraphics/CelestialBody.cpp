#include "CelestialBody.h"

#include "Gizmos.h"
#include "imgui.h"
#include <string>
#include <format>
#include <utility>

CelestialBody::CelestialBody(const Transform& transform, const float radius, const glm::vec4 color,
                             const float rotationSpeed, Actor* parent, std::string name)
	:Actor(transform, parent, std::move(name)), radius(radius), color(color), rotationSpeed(rotationSpeed)
{
}

void CelestialBody::Tick(const float delta)
{
	Actor::Tick(delta);
	glm::vec3 rotation = transform.GetRotation();
	rotation.y += delta * rotationSpeed;
	transform.SetRotation(rotation);

	if (name != "empty")
	{
		Transform t = GlobalTransform();
		glm::vec3 pos = t.GetPosition();
		glm::vec3 rot = t.GetRotation();
		glm::vec3 scale = t.GetScale();

		ImGui::Begin(name.c_str());
		ImGui::Text(std::format("Parent: {}", reinterpret_cast<unsigned long long>(parent)).c_str());
		ImGui::Text(std::format("Position: {}, {}, {}", pos.x, pos.y, pos.z).c_str());
		ImGui::Text(std::format("Rotation: {}, {}, {}", rot.x, rot.y, rot.z).c_str());
		ImGui::Text(std::format("Scale: {}, {}, {}", scale.x, scale.y, scale.z).c_str());
		ImGui::Checkbox("Visible", &visible);
		ImGui::End();
	}
}


void CelestialBody::Draw()
{
	Actor::Draw();
	const auto globalTransform = GlobalTransform();
	aie::Gizmos::addSphere(VEC3_ZERO, radius, 8, 8, color, &globalTransform.matrix);
}
