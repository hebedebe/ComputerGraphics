#include "MeshNode.h"

#include <format>
#include <utility>

#include "CameraNode.h"
#include "ComputerGraphicsApp.h"

void MeshNode::Draw()
{
	Node::Draw();

	m_shaderProgram.bind();

	m_shaderBindFunction(m_shaderProgram, this);

	switch (m_meshType)
	{
	case MeshType::OBJ:
			m_meshObj.Draw();
			break;
	case MeshType::PRIMITIVE:
			m_mesh.Draw();
			break;
	}
}

void MeshNode::Ready()
{
	Node::Ready();
}

void MeshNode::LoadMesh(const char* filename, const bool loadTextures, const bool flipTextureV)
{
	if (m_meshObj.load(filename, loadTextures, flipTextureV))
	{
		SetMesh(m_meshObj);
	}
	else
	{
		throw std::exception("Mesh loading error.");
	}
}

void MeshNode::LoadShader(const aie::eShaderStage shaderStage, const char* filename)
{
	if (!m_shaderProgram.loadShader(shaderStage, filename))
	{
		throw std::exception(std::format("Failed to load shader at {}", filename).c_str());
	}
}

void MeshNode::LinkShader()
{
	if (!m_shaderProgram.link())
	{
		printf(std::format("Shader error: {}", m_shaderProgram.getLastError()).c_str());
		throw std::exception(std::format("Shader error: {}", m_shaderProgram.getLastError()).c_str());
	}
}

void MeshNode::InitialiseStandardShader()
{
	LoadShader(aie::eShaderStage::VERTEX, "./shaders/standard.vert");
	LoadShader(aie::eShaderStage::FRAGMENT, "./shaders/standard.frag");
	LinkShader();
}


void MeshNode::StandardBindFunction(aie::ShaderProgram& program, MeshNode* meshNode)
{
	const auto app = ComputerGraphicsApp::Get();
	const auto tree = meshNode->GetTree();

	CameraNode* camera = tree->GetActiveCamera();

	Transform globalTransform = meshNode->GlobalTransform();
	const glm::mat4 globalTransformMatrix = globalTransform.GetMatrix();

	// Bind light
	program.bindUniform("AmbientColour", glm::vec3(tree->environment.ambientLight));
	program.bindUniform("LightDirection", tree->environment.sunLight.direction);
	program.bindUniform("LightColour", tree->environment.sunLight.diffuse);

	// Bind camera
	program.bindUniform("CameraPosition", camera->GlobalTransform().GetPosition());

	// Bind material
	program.bindUniform("Ka", meshNode->material.ambientColor);
	program.bindUniform("Kd", meshNode->material.diffuseColor);
	program.bindUniform("Ks", meshNode->material.specularColor);
	program.bindUniform("specularPower", meshNode->material.specularPower);

	// Bind transform
	const auto pvm = app->GetProjectionMatrix() * app->GetViewMatrix() * globalTransformMatrix;
	program.bindUniform("ProjectionViewModel", pvm);

	// Bind normal
	program.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(globalTransformMatrix)));
	
	// Bind model
	program.bindUniform("ModelMatrix", globalTransformMatrix);

	const int numLights = tree->environment.registeredLights;
	program.bindUniform("numLights", numLights);
	program.bindUniform("PointLightPosition", numLights, tree->environment.pointLightPositions);
	program.bindUniform("PointLightColour", numLights, tree->environment.pointLightColours);

	program.bindUniform("diffuseTexture", 0);

	meshNode->material.texture.bind(0);
}
