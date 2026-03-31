#include "ParticleEmitter.h"

#include "gl_core_4_4.h"
#include "Particle.h"
#include "Random.h"

ParticleEmitter::ParticleEmitter()
:m_particles(nullptr), m_firstDead(0), m_maxParticles(0), m_vao(0), m_vbo(0),
	m_ibo(0), m_vertexData(nullptr), m_position(0, 0, 0)
{
}

ParticleEmitter::~ParticleEmitter()
{
	printf("Deleting emitter");

	delete[] m_particles;
	delete[] m_vertexData;

	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
}

void ParticleEmitter::Initialise(uint _maxParticles, uint _emitRate, float _lifetimeMin, float _lifetimeMax,
	float _velocityMin, float _velocityMax, float _startSize, float _endSize, const vec4& _startColour,
	const vec4& _endColour)
{
	// Setup emit timers
	m_emitTimer = 0;
	m_emitRate = 1.0f / _emitRate;

	// Store all variables passed in
	m_startColour = _startColour;
	m_endColour = _endColour;
	m_startSize = _startSize;
	m_endSize = _endSize;
	m_velocityMin = _velocityMin;
	m_velocityMax = _velocityMax;
	m_lifespanMin = _lifetimeMin;
	m_lifespanMax = _lifetimeMax;
	m_maxParticles = _maxParticles;

	// Create particle array
	m_particles = new Particle[m_maxParticles];
	m_firstDead = 0;

	// Create the array of vertices for the particles
	// 4 vertices per particle for a quad
	// Will be filled during update
	m_vertexData = new ParticleVertex[m_maxParticles * 4];

	// Create the index buffer data for the particles
	// 6 indices per quad of 2 triangles
	// fill it now as it never changes
	uint* indexData = new uint[m_maxParticles * 6];
	for (uint i = 0; i < m_maxParticles; ++i)
	{
		indexData[i * 6 + 0] = i * 4 + 0;
		indexData[i * 6 + 1] = i * 4 + 1;
		indexData[i * 6 + 2] = i * 4 + 2;
		indexData[i * 6 + 3] = i * 4 + 0;
		indexData[i * 6 + 4] = i * 4 + 2;
		indexData[i * 6 + 5] = i * 4 + 3;
	}

	// Create OpenGL buffers
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(m_maxParticles * 4 * sizeof(ParticleVertex)), m_vertexData, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(m_maxParticles * 6 * sizeof(uint)), indexData, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // Position
	glEnableVertexAttribArray(1); // Colour
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), nullptr);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), (char*)0x10); //THIS MIGHT BREAK

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete[] indexData;
}

void ParticleEmitter::Emit()
{
	// Only emit if there is a dead particle to use
	if (m_firstDead >= m_maxParticles) return;

	// Resurrect the first dead particle
	Particle& particle = m_particles[m_firstDead++];

	// Assign its starting position
	particle.position = m_position;
	
	// Randomise its lifespan
	particle.lifetime = 0;
	particle.lifespan = _RANDF * (m_lifespanMax - m_lifespanMin) + m_lifespanMin;

	// Set starting size and colour
	particle.colour = m_startColour;
	particle.size = m_startSize;

	// randomise velocity direction and strength
	const float speed = _RANDF * (m_velocityMax - m_velocityMin) + m_velocityMin;
	particle.velocity.x = _RANDF * 2 - 1;
	particle.velocity.y = _RANDF * 2 - 1;
	particle.velocity.z = _RANDF * 2 - 1;
	particle.velocity = normalize(particle.velocity) * speed;
}

void ParticleEmitter::Update(const float deltaTime, const mat4& cameraTransform)
{
	// Spawn particles
	m_emitTimer += deltaTime;
	while (m_emitTimer > m_emitRate)
	{
		Emit();
		m_emitTimer -= m_emitRate;
	}

	uint quad = 0;

	// Update particles and turn live particles into billboard quads
	for (uint i = 0; i < m_firstDead; i++)
	{
		Particle* particle = &m_particles[i];

		particle->lifetime += deltaTime;
		if (particle->lifetime >= particle->lifespan)
		{
			// Swap last alive with this one
			*particle = m_particles[m_firstDead - 1];
			m_firstDead--;
		}
		else
		{
			// Move particle
			particle->position += particle->velocity * deltaTime;

			// Size particle
			particle->size = mix(m_startSize, m_endSize, particle->lifetime / particle->lifespan);

			// Colour particle
			particle->colour = mix(m_startColour, m_endColour, particle->lifetime / particle->lifespan);

			// Make a quad the correct size and colour
			const float halfSize = particle->size * 0.5f;

			m_vertexData[quad * 4 + 0].position = vec4(halfSize, halfSize, 0, 1);
			m_vertexData[quad * 4 + 0].colour = particle->colour;

			m_vertexData[quad * 4 + 1].position = vec4(-halfSize, halfSize, 0, 1);
			m_vertexData[quad * 4 + 1].colour = particle->colour;

			m_vertexData[quad * 4 + 2].position = vec4(-halfSize, -halfSize, 0, 1);
			m_vertexData[quad * 4 + 2].colour = particle->colour;

			m_vertexData[quad * 4 + 3].position = vec4(halfSize, -halfSize, 0, 1);
			m_vertexData[quad * 4 + 3].colour = particle->colour;

			// Create billboard transform
			vec3 zAxis = normalize(vec3(cameraTransform[3]) - particle->position);
			vec3 xAxis = cross(vec3(cameraTransform[1]), zAxis);
			vec3 yAxis = cross(zAxis, xAxis);
			mat4 billboard(vec4(xAxis, 0), vec4(yAxis, 0), vec4(zAxis, 0), vec4(0, 0, 0, 1));

			m_vertexData[quad * 4 + 0].position = billboard * m_vertexData[quad * 4 + 0].position + vec4(particle->position, 0);
			
			m_vertexData[quad * 4 + 1].position = billboard * m_vertexData[quad * 4 + 1].position + vec4(particle->position, 0);
			
			m_vertexData[quad * 4 + 2].position = billboard * m_vertexData[quad * 4 + 2].position + vec4(particle->position, 0);
			
			m_vertexData[quad * 4 + 3].position = billboard * m_vertexData[quad * 4 + 3].position + vec4(particle->position, 0);

			quad++;
		}
	}
}

void ParticleEmitter::Draw() const
{
	// Sync the particle vertex buffer
	// Based on how many alive particles there are
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_firstDead * 4 * sizeof(ParticleVertex), m_vertexData);

	// Draw particles
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_firstDead * 6, GL_UNSIGNED_INT, nullptr);
}
