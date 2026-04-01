#pragma once
#include "Node.h"
#include "RenderTarget.h"

class CameraNode :
    public Node
{
public:
	enum class ProjectionMode : uint8_t
	{
		PERSPECTIVE,
		ORTHOGRAPHIC
	};

public:
	// _NODE_DEFAULT_CONSTRUCTOR(CameraNode)
	explicit CameraNode(const Transform& _transform = Transform(), Node* _parent = nullptr, std::string _name = "Camera");

public:
	void Ready() override;
	void Tick(float delta) override;
	void PreDraw() override;

public:
    [[nodiscard]] glm::mat4 GetViewMatrix();
	[[nodiscard]] glm::mat4 GetProjectionMatrix() const;

	void CalculateAspectRatio();
	bool IsValidAspectRatio() const;

    void SetActive(bool active);

	void InitRenderTarget();

	void SetProjectionMode(const ProjectionMode projectionMode) { m_projectionMode = projectionMode; }

public:
	aie::RenderTarget* renderTarget = nullptr;

    float fov = 90.f;
	float width = 16.f;
    float height = 9.f;
	float nearClip = 0.1f;
	float farClip = 1000.f;

protected:
	void OnDestroy() override;

private:
    ProjectionMode m_projectionMode = ProjectionMode::PERSPECTIVE; //Default because orthographic sucks
	bool m_active = false;
	bool m_desiredActive = false;
};
	

