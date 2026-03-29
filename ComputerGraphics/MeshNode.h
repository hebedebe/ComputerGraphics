#pragma once
#include <any>
#include <functional>
#include <map>

#include "Mesh.h"
#include "Node.h"
#include "OBJMesh.h"
#include "Shader.h"

class MeshNode;

typedef std::function<void(aie::ShaderProgram& program, MeshNode* meshNode)> shader_bind_function;

#define _SHADER_BIND_FUNCTION [](aie::ShaderProgram& program, MeshNode* meshNode)

class MeshNode :
    public Node
{
public:
    enum class MeshType
    {
	    OBJ,
        PRIMITIVE
    };

    struct Material
    {
        glm::vec3 ambientColor = _VEC3_ONE;
        glm::vec3 diffuseColor = _VEC3_ONE;
        glm::vec3 specularColor = _VEC3_ONE;
        float specularPower = 1.f;
        aie::Texture texture;
    };

public:
    MeshNode(const Transform& transform, Node* parent = nullptr, std::string name = "MeshNode");

public:
    void Draw() override;
    void Ready() override;

    template <typename T>
    T& GetMesh() { return nullptr; }
    template <>
    Mesh& GetMesh<Mesh>() { return m_mesh; }
    template <>
    aie::OBJMesh& GetMesh<aie::OBJMesh>() { return m_meshObj; }

    void SetMesh(const aie::OBJMesh& mesh) { m_meshObj = mesh; m_meshType = MeshType::OBJ; }
    void SetMesh(const Mesh& mesh) { m_mesh = mesh; m_meshType = MeshType::PRIMITIVE; }
    void LoadMesh(const char* filename, bool loadTextures = true, bool flipTextureV = false);

    aie::ShaderProgram& GetShaderProgram() { return m_shaderProgram; }
    void SetShaderProgram(const aie::ShaderProgram& shaderProgram) { m_shaderProgram = shaderProgram; }
    void LoadShader(aie::eShaderStage shaderStage, const char* filename);
    void LinkShader();
    void InitialiseStandardShader();

    void SetBindFunction(const shader_bind_function& func) { m_shaderBindFunction = func; }

    void SetMeshType(const MeshType meshType) { m_meshType = meshType; }

public:
    Material material;

public:
    static void StandardBindFunction(aie::ShaderProgram& program, MeshNode* meshNode);

protected:
    aie::OBJMesh m_meshObj;
    Mesh m_mesh;
    aie::ShaderProgram m_shaderProgram;
    shader_bind_function m_shaderBindFunction;

    MeshType m_meshType;
};

