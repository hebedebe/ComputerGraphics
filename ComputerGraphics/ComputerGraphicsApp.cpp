#include "ComputerGraphicsApp.h"

#include <iostream>
#include <format>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Gizmos.h"
#include "Input.h"
#include "Node.h"
#include "NodeTree.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

ComputerGraphicsApp::~ComputerGraphicsApp() = default;

ComputerGraphicsApp* ComputerGraphicsApp::Get()
{
	static ComputerGraphicsApp* app = new ComputerGraphicsApp;
	return app;
}

bool ComputerGraphicsApp::startup() {

	const auto startTime = getTime();
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	std::cout << "Startup completed in " << getTime() - startTime << " seconds\n";

	startupCompleteSignal.Emit(this);

	return true;
}

void ComputerGraphicsApp::shutdown() 
{
	delete m_nodeTree;
	m_nodeTree = nullptr;
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

	if (m_nodeTree) m_nodeTree->Tick(deltaTime);

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	if (input->wasKeyPressed(aie::INPUT_KEY_GRAVE_ACCENT))
		m_debug = !m_debug;

}

void ComputerGraphicsApp::draw() 
{
	m_nodeTree->PreDraw();

	m_nodeTree->PostDraw();

	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
}

NodeTree* ComputerGraphicsApp::GetTree() const
{
	return m_nodeTree;
}

ComputerGraphicsApp::ComputerGraphicsApp()
	:Application(), m_nodeTree(new NodeTree)
{
	std::cout << "Constructed ComputerGraphicsApp.\n";
}
