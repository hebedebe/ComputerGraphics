#pragma once

#include <vector>

#include "Application.h"
#include "OBJMesh.h"
#include "Shader.h"
#include "Transform.h"
#include "Node.h"

#include <glm/ext.hpp>

//class Actor;

class ComputerGraphicsApp : public aie::Application {
public:
	static ComputerGraphicsApp* Get();
	~ComputerGraphicsApp() override;

	bool startup() override;
	void shutdown() override;

	void update(float deltaTime) override;
	void draw() override;

	void AddToFreeQueue(Node* node);
	void RegisterNode(Node* node);
	void RemoveNode(Node* node);
	void RegisterPreDraw(Node* node);
	void RemovePreDraw(Node* node);

	[[nodiscard]] glm::mat4 GetViewMatrix() const { return m_viewMatrix; }
	[[nodiscard]] glm::mat4 GetProjectionMatrix() const { return m_projectionMatrix; }

	void SetViewMatrix(const glm::mat4& view) { m_viewMatrix = view; }
	void SetProjectionMatrix(const glm::mat4& projection) { m_projectionMatrix = projection; }

private:
	ComputerGraphicsApp();

protected:

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	glm::vec4 m_backgroundColour = glm::vec4(0, 0, 0, 1.f);


	float m_timeScale = 1.f;

	std::vector<Node*> m_nodes; // List of nodes in the scene
	std::vector<Node*> m_preDrawNodes; // Execute between tick and draw (for objects like the camera which need to update the app's projection matrix)
	std::vector<Node*> m_freeQueue;

	bool m_vsync = true;
};
