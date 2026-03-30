#include "PostProcessNode.h"

#include <format>
#include <utility>

#include "ComputerGraphicsApp.h"
#include "imgui.h"


PostProcessNode::PostProcessNode(Transform transform, Node* parent, std::string name)
	:Node(std::move(transform), parent, std::move(name))
{
}

void PostProcessNode::Tick(float delta)
{
	Node::Tick(delta);

	_IF_NOT_DEBUG return;

	ImGui::Begin("Postprocess");
	ImGui::InputText("Path", m_filePathBuffer, 64);
	if (ImGui::Button("Load fragment"))
	{
		m_shader = aie::ShaderProgram();
		SetEffect(m_filePathBuffer);
	}
	ImGui::End();
}

void PostProcessNode::Ready()
{
	Node::Ready();
	
	/*m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/post.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/post.frag");
	if (!m_shader.link())
	{
		printf(std::format("Shader error: {}", m_shader.getLastError()).c_str());
		throw std::exception(std::format("Shader error: {}", m_shader.getLastError()).c_str());
	}*/

	m_screenQuad.InitialiseFullscreenQuad();

	m_tree->RegisterPostDraw(this);
}

void PostProcessNode::PostDraw()
{
	Node::PostDraw();

	const auto app = ComputerGraphicsApp::Get();

	if (not sourceTarget) return;

	app->clearScreen();
	
	m_shader.bind();
	m_shader.bindUniform("colourTarget", 0);

	sourceTarget->getTarget(0).bind(0);

	m_screenQuad.Draw();

}

void PostProcessNode::SetEffect(const char* filepath)
{
	m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/post.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, filepath);
	if (!m_shader.link())
	{
		printf(std::format("Shader error: {}", m_shader.getLastError()).c_str());
		throw std::exception(std::format("Shader error: {}", m_shader.getLastError()).c_str());
	}
}
