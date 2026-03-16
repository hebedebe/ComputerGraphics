#pragma once
#include "Actor.h"
class Disc :
    public Actor
{
public:
    Disc(const Transform& transform, float innerRadius, float outerRadius, glm::vec4 color, Actor* parent = nullptr, std::string name = "Disc");

public:
    void Draw() override;

public:
    float innerRadius;
    float outerRadius;
    glm::vec4 color;
};

