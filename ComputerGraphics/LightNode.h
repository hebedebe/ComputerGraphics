#pragma once

#include "Node.h"
#include "Light.h"
#include "Mesh.h"

class LightNode :
    public Node
{
public:
    explicit LightNode(const Transform& transform, Node* parent = nullptr, std::string name = "Light", const Light& light = {
	                       .diffuse = glm::vec3{1,0,0}, .specular = glm::vec3{1}, .direction = glm::vec3{0}});

public:
    void UpdateLightData();
    Light GetLightData() const;

    void Ready() override;
    void Tick(float delta) override;
    void Draw() override;

protected:
    void OnDestroy() override;
    void RebuildLight();

protected:
    Light m_lightData;

    bool m_debug = false;
};

