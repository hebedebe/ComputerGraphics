#include "ComputerGraphicsApp.h"

#include <iostream>

#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Actor.h"
#include "imgui.h"
#include "Transform.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

ComputerGraphicsApp::~ComputerGraphicsApp() {

}

ComputerGraphicsApp* ComputerGraphicsApp::Get()
{
	static ComputerGraphicsApp* app = new ComputerGraphicsApp;
	return app;
}

bool ComputerGraphicsApp::startup() {
	
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(m_cameraDistance), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);

	m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");

	if (m_shader.link() == false)
	{
		printf("Shader Error: %s\n", m_shader.getLastError());
		return false;
	}


	m_quadMesh.InitialiseCube();

	// Make the quad 10 units wide
	m_quadTransform.SetScale(vec3(10));

	return true;
}

void ComputerGraphicsApp::shutdown() {

	Gizmos::destroy();
}

void ComputerGraphicsApp::update(float deltaTime) {

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
						vec3(-10 + i, 0, -10),
						i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
						vec3(-10, 0, -10 + i),
						i == 10 ? white : black);
	}

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	auto scroll = input->getMouseScroll();
	m_viewMatrix = glm::lookAt(vec3(m_cameraDistance - scroll*5), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Background Colour", glm::value_ptr(m_backgroundColour));
	ImGui::SliderFloat("Timescale", &m_timeScale, 0.1, 15, "%.3f", 3);
	if (ImGui::Button("Reset timescale")) m_timeScale = 1.f;
	ImGui::End();

	for (const auto actor : m_actors)
	{
		actor->Tick(deltaTime*m_timeScale);
	}

	for (const auto actor : m_freeQueue)
	{
		actor->Free();
	}
	m_freeQueue.clear();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	m_quadTransform.matrix = rotate(m_quadTransform.matrix, m_quadTransform.GetRotation().y + deltaTime, vec3(0, 1, 0));

}

void ComputerGraphicsApp::draw() {

	// wipe the screen to the background colour
	setBackgroundColour(m_backgroundColour.r, m_backgroundColour.g, m_backgroundColour.b, m_backgroundColour.a);
	clearScreen();

	// update perspective based on screen size
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);

	for (const auto actor : m_actors)
	{
		if (actor->visible)
			actor->Draw();
	}

	Gizmos::draw(m_projectionMatrix * m_viewMatrix);

	// Bind shader
	m_shader.bind();

	// Bind transform
	auto pvm = m_projectionMatrix * m_viewMatrix * m_quadTransform.matrix;
	m_shader.bindUniform("ProjectionViewModel", pvm);

	// Draw quad
	m_quadMesh.Draw();
}

void ComputerGraphicsApp::AddToFreeQueue(Actor* body)
{
	m_freeQueue.emplace_back(body);
}

void ComputerGraphicsApp::RegisterBody(Actor* body)
{
	m_actors.emplace_back(body);
}

void ComputerGraphicsApp::RemoveBody(Actor* body)
{
	m_actors.erase(std::ranges::find(m_actors, body));
}

ComputerGraphicsApp::ComputerGraphicsApp()
{
	std::cout << "Constructed ComputerGraphicsApp.\n";
}
