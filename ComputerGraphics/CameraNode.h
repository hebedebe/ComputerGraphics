#pragma once
#include "Node.h"

class CameraNode :
    public Node
{
public:
	explicit CameraNode(const Transform& transform, Node* parent = nullptr, std::string name = "Camera");

public:
	void Tick(float delta) override;

	void PreDraw() override;

    [[nodiscard]] glm::mat4 GetViewMatrix() const;
	[[nodiscard]] glm::mat4 GetProjectionMatrix() const;

    void SetActive(bool active);

public:
    float fov = 90.f;
	float width = 16.f;
    float height = 9.f;
	float nearClip = 0.1f;
	float farClip = 1000.f;

protected:
	void OnDestroy() override;

private:
    bool m_active = false;
};

