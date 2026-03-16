#pragma once

#include <vector>

#include "Application.h"
#include <glm/mat4x4.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"

class Actor;

class ComputerGraphicsApp : public aie::Application {
public:
	static ComputerGraphicsApp* Get();
	~ComputerGraphicsApp() override;

	bool startup() override;
	void shutdown() override;

	void update(float deltaTime) override;
	void draw() override;

	void AddToFreeQueue(Actor* body);
	void RegisterBody(Actor* body);
	void RemoveBody(Actor* body);

private:
	ComputerGraphicsApp();

protected:

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;
	float m_cameraDistance = 10;

	glm::vec4 m_backgroundColour = glm::vec4(0, 0, 0, 1.f);


	float m_timeScale = 1.f;

	Mesh m_quadMesh;
	Transform m_quadTransform;
	aie::ShaderProgram m_shader;

	std::vector<Actor*> m_actors;
	std::vector<Actor*> m_freeQueue;
};
