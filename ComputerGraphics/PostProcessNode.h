#pragma once
#include "Mesh.h"
#include "Node.h"
#include "RenderTarget.h"
#include "Shader.h"

struct PostProcessEffect
{
    aie::ShaderProgram program;

public:
    PostProcessEffect(const char* fragPath);
};

class PostProcessNode :
    public Node
{
public:
    PostProcessNode(Transform transform, Node* parent = nullptr, std::string name = "PostProcess");

public:
    void Ready() override;
    void PostDraw() override;

public:
    void AddEffect(const PostProcessEffect& effect);

public:
    aie::RenderTarget* sourceTarget;

protected:
    std::vector<PostProcessEffect> m_effects;

    aie::RenderTarget m_bufferOne;
    aie::RenderTarget m_bufferTwo;

    Mesh m_screenQuad;

    aie::ShaderProgram m_defaultShader;
};

