#include "ComputerGraphicsApp.h"

#include <iostream>

#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Actor.h"
#include "CelestialBody.h"
#include "Disc.h"
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
	m_viewMatrix = glm::lookAt(vec3(150), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);

	auto origin = new Actor(Transform());
	auto sun = new CelestialBody(Transform(), 15, YELLOW, 0.1, nullptr, "Sun");
	auto mercury = new CelestialBody(Transform(glm::vec3(0,0,20)), 0.3, RED, 365.f/176, nullptr, "Mercury");
	auto mercuryContainer = new CelestialBody(Transform(glm::vec3(0,0,0)), 0, RED, 365.f/176);
	auto venus = new CelestialBody(Transform(glm::vec3(0,0,30)), 0.6, RED, 365.f/225, nullptr, "Venus");
	auto venusContainer = new CelestialBody(Transform(glm::vec3(0,0,0)), 0, RED, 365.f/225);
	auto earth = new CelestialBody(Transform(glm::vec3(0,0, 40)), 0.6, RED, 365.f/365, nullptr, "Earth");
	auto earthContainer = new CelestialBody(Transform(glm::vec3(0,0, 0)), 0, RED, 365.f/365);
	auto mars = new CelestialBody(Transform(glm::vec3(0,0,50)), 0.2, RED, 365.f/687, nullptr, "Mars");
	auto marsContainer = new CelestialBody(Transform(glm::vec3(0,0,0)), 0, RED, 365.f/687);
	auto jupiter = new CelestialBody(Transform(glm::vec3(0,0,60)), 6.9, RED, 365.f/365*12, nullptr, "Jupiter");
	auto jupiterContainer = new CelestialBody(Transform(glm::vec3(0,0,0)), 0, RED, 365.f/365/12);
	auto saturn = new CelestialBody(Transform(glm::vec3(0,0,85)), 5.8, RED, 365.f/365/29.4, nullptr, "Saturn");
	auto saturnContainer = new CelestialBody(Transform(glm::vec3(0,0,0)), 0, RED, 365.f/365/29.4);
	auto uranus = new CelestialBody(Transform(glm::vec3(0,0,100)), 2.5, RED, 365.f/365/84, nullptr, "Uranus");
	auto uranusContainer = new CelestialBody(Transform(glm::vec3(0,0,0)), 0, RED, 365.f/365/84);
	auto neptune = new CelestialBody(Transform(glm::vec3(0,0,115)), 2.4, RED, 365.f/365/165, nullptr, "Neptune");
	auto neptuneContainer = new CelestialBody(Transform(glm::vec3(0,0,0)), 0, RED, 365.f/365/165);

	origin->AddChild(sun);

	sun->AddChild(mercuryContainer);
	sun->AddChild(venusContainer);
	sun->AddChild(earthContainer);
	sun->AddChild(marsContainer);
	sun->AddChild(jupiterContainer);
	sun->AddChild(saturnContainer);
	sun->AddChild(uranusContainer);
	sun->AddChild(neptuneContainer);

	mercuryContainer->AddChild(mercury);
	venusContainer->AddChild(venus);
	earthContainer->AddChild(earth);
	marsContainer->AddChild(mars);
	jupiterContainer->AddChild(jupiter);
	saturnContainer->AddChild(saturn);
	uranusContainer->AddChild(uranus);
	neptuneContainer->AddChild(neptune);

	auto moonContainer = new CelestialBody(Transform(), 0, RED, 1);
	auto moon = new CelestialBody(Transform(vec3(0, 0, 2)), 0.2, RED, 1, nullptr, "Moon");

	earth->AddChild(moonContainer);
	moonContainer->AddChild(moon);

	auto saturnDisc = new Disc(Transform(), 6.5, 8, GREEN);
	auto jupiterDisc = new Disc(Transform(), 8, 11, GREEN);
	auto neptuneDisc = new Disc(Transform(), 3, 4.5, GREEN);

	saturn->AddChild(saturnDisc);
	jupiter->AddChild(jupiterDisc);
	neptune->AddChild(neptuneDisc);


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
