#pragma once
#include "Mesh.h"
#include "Node.h"
#include "RenderTarget.h"
#include "Shader.h"

class PostProcessNode :
    public Node
{
public:
    PostProcessNode(Transform transform, Node* parent = nullptr, std::string name = "PostProcess");

public:
    void Ready() override;
    void PostDraw() override;

public:
    void SetEffect(const char* filepath);

public:
    aie::RenderTarget* sourceTarget;

protected:
    Mesh m_screenQuad;

    aie::ShaderProgram m_shader;
};

