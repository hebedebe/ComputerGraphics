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

	void AddToFreeQueue(Node* body);
	void RegisterBody(Node* body);
	void RemoveBody(Node* body);

	glm::mat4 GetViewMatrix() const { return m_viewMatrix; }
	glm::mat4 GetProjectionMatrix() const { return m_projectionMatrix; }

private:
	ComputerGraphicsApp();

protected:

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;
	float m_cameraDistance = 10;

	glm::vec4 m_backgroundColour = glm::vec4(0, 0, 0, 1.f);


	float m_timeScale = 1.f;

	std::vector<Node*> m_actors;
	std::vector<Node*> m_freeQueue;

	bool m_vsync = true;
};
