#pragma once

#include <glm/glm.hpp>

#include "gl_core_4_4.h"

class Mesh
{
public:
	Mesh() : m_triCount(0), m_vao(0), m_vbo(0), m_ibo(0) {}
	virtual ~Mesh();

	struct Vertex
	{
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec2 texCoord;
	};

	void Initialise(const unsigned long vertexCount, const Vertex* vertices, const unsigned int indexCount = 0, const unsigned int* indices = nullptr);

	void InitialiseQuad();
	void InitialiseCube();
	void InitialisePyramid();
	void InitialiseCylinder(float radius = 0.5f, float height = 1.f, unsigned int segments = 12);
	void InitialiseCone(float radius=0.5f, float height=1.f, unsigned int segments = 12);

	virtual void Draw();

public:
	static Mesh MakeQuad();
	static Mesh MakeCube();
	static Mesh MakePyramid();
	static Mesh MakeCylinder(float radius = 0.5f, float height = 1.f, unsigned int segments = 12);
	static Mesh MakeCone(float radius = 0.5f, float height = 1.f, unsigned int segments = 12);
	static Mesh Make(const unsigned long vertexCount, const Vertex* vertices, const unsigned int indexCount = 0, const unsigned int* indices = nullptr);

protected:
	unsigned int m_triCount;
	unsigned int m_vao, m_vbo, m_ibo;
};

