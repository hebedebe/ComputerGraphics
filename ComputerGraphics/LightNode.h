#pragma once
#include "Node.h"
class LightNode :
    public Node
{
public:
    struct Light
    {
        glm::vec3 direction;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };

public:
    explicit LightNode(const Transform& transform, Node* parent = nullptr, std::string name = "Light", Light light = {
	                       .direction = glm::vec3{0}, .diffuse = glm::vec3{1}, .specular = glm::vec3{1}});

public:
    void UpdateLightData();
    Light GetLightData() const;

protected:
    Light m_lightData;
};

