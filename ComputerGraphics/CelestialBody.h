#pragma once
#include "Actor.h"
class CelestialBody :
    public Actor
{
public:
    CelestialBody(const Transform& transform, float radius, glm::vec4 color, float rotationSpeed, Actor* parent = nullptr, std::string name = "empty");

public:
    void Tick(float delta) override;
    void Draw() override;

public:
    float radius;
    glm::vec4 color;
    float rotationSpeed;
};

