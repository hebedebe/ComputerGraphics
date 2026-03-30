#pragma once

#include <vector>
#include <glm/ext.hpp>

#include "Application.h"
#include "OBJMesh.h"
#include "Shader.h"
#include "Environment.h"
#include "Node.h"


#define _DEBUG_ENABLED ComputerGraphicsApp::Get()->GetDebug()
#define _IF_DEBUG if (_DEBUG_ENABLED)
#define _IF_NOT_DEBUG if (!_DEBUG_ENABLED)

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

	void SetDebug(const bool debug) { m_debug = debug; }
	bool GetDebug() const { return m_debug; }

protected:
	NodeTree* m_nodeTree;

	bool m_vsync = true;

	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	bool m_debug = false;

private:
	ComputerGraphicsApp();
};
