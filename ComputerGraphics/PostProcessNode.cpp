#include "PostProcessNode.h"

#include <format>
#include <utility>

#include "ComputerGraphicsApp.h"


PostProcessEffect::PostProcessEffect(const char* fragPath)
{
	program.loadShader(aie::eShaderStage::VERTEX, "./shaders/post.vert");
	program.loadShader(aie::eShaderStage::FRAGMENT, fragPath);
	if (!program.link())
	{
		printf(std::format("Shader error: {}", program.getLastError()).c_str());
		throw std::exception(std::format("Shader error: {}", program.getLastError()).c_str());
	}
	printf("Loaded post process fragment %s\n", fragPath);
}

PostProcessNode::PostProcessNode(Transform transform, Node* parent, std::string name)
	:Node(std::move(transform), parent, std::move(name))
{
}

void PostProcessNode::Ready()
{
	Node::Ready();
	
	m_defaultShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/post.vert");
	m_defaultShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/post.frag");
	if (!m_defaultShader.link())
	{
		printf(std::format("Shader error: {}", m_defaultShader.getLastError()).c_str());
		throw std::exception(std::format("Shader error: {}", m_defaultShader.getLastError()).c_str());
	}

	const auto app = ComputerGraphicsApp::Get();

	m_bufferOne.initialise(1, app->getWindowWidth(), app->getWindowHeight());
	m_bufferTwo.initialise(1, app->getWindowWidth(), app->getWindowHeight());

	m_screenQuad.InitialiseFullscreenQuad();

	m_tree->RegisterPostDraw(this);
}

void PostProcessNode::PostDraw()
{
	Node::PostDraw();

	const auto app = ComputerGraphicsApp::Get();

	if (not sourceTarget) return;

	app->clearScreen();

	if (m_effects.empty())
	{
		m_defaultShader.bind();
		m_defaultShader.bindUniform("colourTarget", 0);

		sourceTarget->getTarget(0).bind(0);

		m_screenQuad.Draw();
		return;
	}

	m_bufferOne.bind();
	app->clearScreen();
	m_defaultShader.bind();
	m_defaultShader.bindUniform("colourTarget", 0);
	sourceTarget->getTarget(0).bind(0);
	m_screenQuad.Draw();
	m_bufferOne.unbind();

	aie::RenderTarget* target = nullptr;
	aie::RenderTarget* source = nullptr;

	for (size_t i = 0; i < m_effects.size(); i++)
	{
		if (i % 2 != 0)
		{
			target = &m_bufferOne;
			source = &m_bufferTwo;
		}
		else
		{
			target = &m_bufferTwo;
			source = &m_bufferOne;
		}

		target->bind();
		app->clearScreen();

		m_effects[i].program.bind();
		m_effects[i].program.bindUniform("colourTarget", 0);

		source->getTarget(0).bind(0);
		
		m_screenQuad.Draw();

		target->unbind();
	}

	m_defaultShader.bind();
	m_defaultShader.bindUniform("colourTarget", 0);
	target->getTarget(0).bind(0);
	m_screenQuad.Draw();
}

void PostProcessNode::AddEffect(const PostProcessEffect& effect)
{
	m_effects.emplace_back(effect);
}
