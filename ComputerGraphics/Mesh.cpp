#include "Mesh.h"

#include "gl_core_4_4.h"

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Mesh::Initialise(const unsigned long vertexCount, const Vertex* vertices, const unsigned int indexCount, const unsigned int* indices)
{
	assert(vao == 0);

	// Generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	// Bind vertex array aka a mesh wrapper
	glBindVertexArray(vao);

	// Bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)sizeof(Vertex) * vertexCount, vertices, GL_STATIC_DRAW);

	// Enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

	// Bind indices if there are any
	if (indexCount != 0)
	{
		glGenBuffers(1, &ibo);

		// Bind vertex buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		// Fill vertex buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)sizeof(unsigned int) * indexCount, indices, GL_STATIC_DRAW);

		triCount = indexCount / 3;
	} else
	{
		triCount = vertexCount / 3;
	}

	// Unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::InitialiseQuad()
{
	// Check that the mesh is not initialised already
	assert(vao == 0);

	// Generate Buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	// Bind vertex array aka a mesh wrapper
	glBindVertexArray(vao);

	// Bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Define 6 vertices for 2 triangles
	Vertex vertices[6];
	vertices[0].position = { -0.5f, 0, 0.5f, 1 };
	vertices[1].position = { 0.5f, 0, 0.5f, 1 };
	vertices[2].position = { -0.5f, 0, -0.5f, 1 };

	vertices[3].position = { -0.5f, 0, -0.5f, 1 };
	vertices[4].position = { 0.5f, 0, 0.5f, 1 };
	vertices[5].position = { 0.5f, 0, -0.5f, 1 };

	// Fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	// Enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

	// Unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Quad has 2 triangles
	triCount = 2;
}

void Mesh::InitialiseCube()
{
	// Check that the mesh is not initialised already
	assert(vao == 0);

	// Define 8 vertices for 12 triangles
	Vertex vertices[8];
	
	// Bottom face
	vertices[0].position = { -0.5f, -0.5, 0.5f, 1 };
	vertices[1].position = { 0.5f, -0.5, 0.5f, 1 };
	vertices[2].position = { -0.5f, -0.5, -0.5f, 1 };
	vertices[3].position = { 0.5f, -0.5, -0.5f, 1 };

	// Top face
	vertices[4].position = { -0.5f, 0.5f, 0.5f, 1 };
	vertices[5].position = { 0.5f, 0.5f, 0.5f, 1 };
	vertices[6].position = { -0.5f, 0.5f, -0.5f, 1 };
	vertices[7].position = { 0.5f, 0.5f, -0.5f, 1 };

	constexpr unsigned int indexCount = 36;
	const unsigned int indices[indexCount] = {
		4, 5, 6, //Top
		6, 5, 7,

		2, 1, 0, //Bottom
		3, 1, 2,

		6, 3, 2, // Front
		7, 3, 6,

		0, 1, 4, // Back
		1, 5, 4,

		0, 6, 2, // Left
		0, 4, 6,

		1, 3, 7, // Right
		7, 5, 1,
	};

	Initialise(8, vertices, indexCount, indices);
}

void Mesh::InitialisePyramid()
{
	// Check that the mesh is not initialised already
	assert(vao == 0);

	// Define 5 vertices for 10 triangles
	Vertex vertices[5];

	// Bottom face
	vertices[0].position = { -0.5f, -0.5, 0.5f, 1 };
	vertices[1].position = { 0.5f, -0.5, 0.5f, 1 };
	vertices[2].position = { -0.5f, -0.5, -0.5f, 1 };
	vertices[3].position = { 0.5f, -0.5, -0.5f, 1 };

	// Top point
	vertices[4].position = { 0.f, 0.5f, 0.f, 1 };

	constexpr unsigned int indexCount = 18;
	const unsigned int indices[indexCount] = {
		2, 1, 0, //Bottom
		3, 1, 2,

		0, 1, 4, // Back

		2, 0, 4, // Left

		3, 2, 4, // Front

		1, 3, 4 // Right
	};

	Initialise(8, vertices, indexCount, indices);
}

void Mesh::Draw()
{
	glBindVertexArray(vao);
	// using indices or just vertices?
	if (ibo != 0)
		glDrawElements(GL_TRIANGLES, (GLsizei)triCount * 3, GL_UNSIGNED_INT, nullptr);
	else
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)triCount * 3);
}
