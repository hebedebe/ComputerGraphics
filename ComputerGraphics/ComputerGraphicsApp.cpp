#include "ComputerGraphicsApp.h"

#include <iostream>
#include <format>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "CameraNode.h"
#include "Gizmos.h"
#include "Input.h"
#include "Node.h"
#include "imgui.h"
#include "MeshNode.h"
#include "MotionNode.h"
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
	
	auto startTime = getTime();
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	auto bunnyMesh = new MeshNode(Transform());
	bunnyMesh->LoadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");
	bunnyMesh->LoadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");
	bunnyMesh->LinkShader();
	bunnyMesh->LoadMesh("./models/bunny.obj");

	std::cout << bunnyMesh->transform.ToString().c_str() << "\n";

	auto camera = new CameraNode(Transform(vec3(0, 5, 10), vec3(-0.5f, 0, 0)));
	camera->SetActive(true);

	camera->transform.SetPosition(vec3(0,-10,-10));
	camera->transform.SetRotationDegrees(vec3(45, 0, 0));

	std::cout << "Startup completed in " << getTime() - startTime << " seconds\n";
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

	ImGui::Begin("Debug");
	ImGui::ColorEdit4("Background Colour", glm::value_ptr(m_backgroundColour));
	ImGui::SliderFloat("Timescale", &m_timeScale, 0.1f, 15, "%.3f", 3);
	if (ImGui::Button("Reset timescale")) m_timeScale = 1.f;
	ImGui::Text(std::format("Fps: {}", getFPS()).c_str());
	bool newVsync = m_vsync;
	ImGui::Checkbox("VSync", &newVsync);
	if (m_vsync != newVsync)
	{
		setVSync(newVsync);
		m_vsync = newVsync;
	}
	ImGui::End();


	for (const auto node : m_nodes)
	{
		node->Tick(deltaTime*m_timeScale);
	}

	for (const auto node : m_freeQueue)
	{
		node->Free();
	}
	m_freeQueue.clear();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

}

void ComputerGraphicsApp::draw() {

	// wipe the screen to the background colour
	setBackgroundColour(m_backgroundColour.r, m_backgroundColour.g, m_backgroundColour.b, m_backgroundColour.a);
	clearScreen();

	for (const auto node : m_preDrawNodes)
	{
		node->PreDraw();
	}

	for (const auto node : m_nodes)
	{
		if (node->visible)
			node->Draw();
	}

	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
}

void ComputerGraphicsApp::AddToFreeQueue(Node* node)
{
	m_freeQueue.emplace_back(node);
}

void ComputerGraphicsApp::RegisterNode(Node* node)
{
	m_nodes.emplace_back(node);
}

void ComputerGraphicsApp::RemoveNode(Node* node)
{
	m_nodes.erase(std::ranges::find(m_nodes, node));
}

void ComputerGraphicsApp::RegisterPreDraw(Node* node)
{
	m_preDrawNodes.emplace_back(node);
}

void ComputerGraphicsApp::RemovePreDraw(Node* node)
{
	const auto iter = std::ranges::find(m_preDrawNodes, node);
	if (iter != m_preDrawNodes.end())
		m_preDrawNodes.erase(iter);

}

ComputerGraphicsApp::ComputerGraphicsApp()
{
	std::cout << "Constructed ComputerGraphicsApp.\n";
}
