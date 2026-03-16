#pragma once

#include <glm/glm.hpp>

#include "gl_core_4_4.h"

class Mesh
{
public:
	Mesh() : triCount(0), vao(0), vbo(0), ibo(0) {}
	virtual ~Mesh();

	struct Vertex
	{
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec4 texCoord;
	};

	void Initialise(const unsigned long vertexCount, const Vertex* vertices, const unsigned int indexCount = 0, const unsigned int* indices = nullptr);

	void InitialiseQuad();
	void InitialiseCube();

	virtual void Draw();

protected:
	unsigned int triCount;
	unsigned int vao, vbo, ibo;
};

