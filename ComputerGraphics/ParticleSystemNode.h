#pragma once
#include "Node.h"
#include "ParticleEmitter.h"
#include "Shader.h"

class ParticleSystemNode :
    public Node
{
public:
    ParticleSystemNode(const Transform& _transform = Transform(), Node* _parent = nullptr, std::string _name = "Particle System");

public:
    void Ready() override;
    void Tick(float delta) override;
    void Draw() override;

public:
    ParticleEmitter emitter;
    aie::ShaderProgram shader;
    std::function<void(aie::ShaderProgram& program)> shaderBindFunction;

protected:
    void OnDestroy() override;
};

