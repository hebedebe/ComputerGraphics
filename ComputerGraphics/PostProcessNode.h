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
    void Tick(float delta) override;
    void Ready() override;
    void PostDraw() override;

public:
    void SetEffect(const char* filepath);
    void InitOutputTarget();

public:
    aie::RenderTarget* sourceTarget;
    aie::RenderTarget* outputTarget = nullptr;

protected:
    void OnDestroy() override;

protected:
    Mesh m_screenQuad;

    aie::ShaderProgram m_shader;


private:
    char m_filePathBuffer[64] = "Enter path here (64 char max)";
};

