#pragma once

#include <vector>
#include <glm/ext.hpp>

#include "Application.h"
#include "OBJMesh.h"
#include "Shader.h"
#include "Environment.h"
#include "Node.h"


//class Actor;

class NodeTree;
class CameraNode;

class ComputerGraphicsApp : public aie::Application {
public:
	static ComputerGraphicsApp* Get();
	~ComputerGraphicsApp() override;

public:
	bool startup() override;
	void shutdown() override;

	void update(float deltaTime) override;
	void draw() override;

public:
	[[nodiscard]] glm::mat4 GetViewMatrix() const { return m_viewMatrix; }
	[[nodiscard]] glm::mat4 GetProjectionMatrix() const { return m_projectionMatrix; }

	void SetViewMatrix(const glm::mat4& view) { m_viewMatrix = view; }
	void SetProjectionMatrix(const glm::mat4& projection) { m_projectionMatrix = projection; }

	NodeTree* GetTree() const;

protected:
	NodeTree* m_nodeTree;

	bool m_vsync = true;

	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

private:
	ComputerGraphicsApp();
};
