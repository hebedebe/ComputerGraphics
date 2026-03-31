#include "ParticleSystemNode.h"

#include <utility>

#include "CameraNode.h"
#include "ComputerGraphicsApp.h"

ParticleSystemNode::ParticleSystemNode(const Transform& _transform, Node* _parent, std::string _name)
	:Node(_transform, _parent, std::move(_name))
{
	shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/particle.vert");
	shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/particle.frag");
	shader.link();
}

void ParticleSystemNode::Ready()
{
	Node::Ready();
	if (!shaderBindFunction)
	{
		shaderBindFunction = [this](aie::ShaderProgram& program)
		{
			const auto app = ComputerGraphicsApp::Get();

			program.bindUniform("ProjectionViewModel", app->GetBasePvm() * GlobalTransform().GetMatrix());
		};
	}
}

void ParticleSystemNode::Tick(const float delta)
{
	Node::Tick(delta);

	if (const auto activeCamera = m_tree->GetActiveCamera())
		emitter.Update(delta, activeCamera->GlobalTransform().GetMatrix());
}

void ParticleSystemNode::Draw()
{
	Node::Draw();

	shader.bind();
	shaderBindFunction(shader);

	emitter.Draw();
}

void ParticleSystemNode::OnDestroy()
{
	Node::OnDestroy();
	printf("Destroying particle system node");
}
