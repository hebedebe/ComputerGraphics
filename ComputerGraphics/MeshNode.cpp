#include "MeshNode.h"

#include <format>
#include <utility>

#include "ComputerGraphicsApp.h"

MeshNode::MeshNode(const Transform& transform, Node* parent, std::string name)
	:Node(transform, parent, std::move(name)), m_shaderBindFunction(&DefaultShaderBindFunction)
{
}

void MeshNode::Draw()
{
	Node::Draw();

	m_shaderProgram.bind();

	m_shaderBindFunction(m_shaderProgram, this);

	m_mesh.draw();
}

void MeshNode::LoadMesh(const char* filename)
{
	if (!m_mesh.load(filename))
	{
		throw std::exception("Mesh loading error.");
	}
}

void MeshNode::LoadShader(const aie::eShaderStage shaderStage, const char* filename)
{
	m_shaderProgram.loadShader(shaderStage, filename);
}

void MeshNode::LinkShader()
{
	if (!m_shaderProgram.link())
	{
		throw std::exception(std::format("Shader error: {}", m_shaderProgram.getLastError()).c_str());
	}
}

void MeshNode::DefaultShaderBindFunction(aie::ShaderProgram& program, MeshNode* meshNode)
{
	const auto* app = ComputerGraphicsApp::Get();
	const auto pvm = app->GetProjectionMatrix() * app->GetViewMatrix() * meshNode->GlobalTransform().matrix;
	program.bindUniform("ProjectionViewModel", pvm);
}
