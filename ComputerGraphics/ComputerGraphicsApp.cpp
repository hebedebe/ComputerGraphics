#include "ComputerGraphicsApp.h"

#include <iostream>
#include <format>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "CameraNode.h"
#include "Gizmos.h"
#include "Input.h"
#include "LightNode.h"
#include "Node.h"
#include "MeshNode.h"
#include "NodeTree.h"
#include "PostProcessNode.h"
#include "ProfilerNode.h"
#include "Transform.h"

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

	const auto mesh = new MeshNode(Transform());
	mesh->LoadMesh("./models/soulspear/soulspear.obj", true, true);
	//a->SetMeshType(MeshNode::MeshType::OBJ);
	mesh->InitialiseStandardShader();

	auto light = new LightNode(Transform());
	light->transform.Move({0,0,2});

	const auto camera = new CameraNode(Transform(vec3(0, 5, 10), vec3(-0.5f, 0, 0)));
	camera->SetActive(true);
	camera->InitRenderTarget();

	const auto profiler = new ProfilerNode;

	const auto postProcess = new PostProcessNode(Transform());
	postProcess->sourceTarget = camera->renderTarget;
	postProcess->SetEffect("./shaders/post_blur.frag");

	camera->transform.SetPosition(vec3(0,-10,-10));
	camera->transform.SetRotationDegrees(vec3(45, 0, 0));

	std::cout << "Startup completed in " << getTime() - startTime << " seconds\n";
	return true;
}

void ComputerGraphicsApp::shutdown() 
{
	delete m_nodeTree;
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
	:m_nodeTree(new NodeTree)
{
	std::cout << "Constructed ComputerGraphicsApp.\n";
}
