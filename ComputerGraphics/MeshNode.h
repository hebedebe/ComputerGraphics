#pragma once
#include <any>
#include <functional>
#include <map>

#include "Node.h"
#include "OBJMesh.h"
#include "Shader.h"

class MeshNode;

typedef std::function<void(aie::ShaderProgram& program, MeshNode* meshNode)> shader_bind_function;

class MeshNode :
    public Node
{
public:
    

public:
    MeshNode(const Transform& transform, Node* parent = nullptr, std::string name = "MeshNode");

public:
    void Draw() override;

    aie::OBJMesh& GetMesh() { return m_mesh; }
    void SetMesh(const aie::OBJMesh& mesh) { m_mesh = mesh; }
    void LoadMesh(const char* filename);

    aie::ShaderProgram& GetShaderProgram() { return m_shaderProgram; }
    void SetShaderProgram(const aie::ShaderProgram& shaderProgram) { m_shaderProgram = shaderProgram; }
    void LoadShader(aie::eShaderStage shaderStage, const char* filename);
    void LinkShader();

    void SetBindFunction(const shader_bind_function& func) { m_shaderBindFunction = func; }

protected:
    static void DefaultShaderBindFunction(aie::ShaderProgram& program, MeshNode* meshNode);

protected:
    aie::OBJMesh m_mesh;
    aie::ShaderProgram m_shaderProgram;
    shader_bind_function m_shaderBindFunction;
};

