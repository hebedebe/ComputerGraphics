#pragma once
#include <glm/glm.hpp>

#include "gl_core_4_4.h"

using namespace glm;

class ParticleEmitter
{
	friend class ParticleSystemNode;

public:
	ParticleEmitter();
	virtual ~ParticleEmitter();

public:
	void Initialise(uint _maxParticles, uint _emitRate, float _lifetimeMin, float _lifetimeMax, float _velocityMin, 
		float _velocityMax, float _startSize, float _endSize, const vec4& _startColour, const vec4& _endColour);
	void Emit();
	void Update(float deltaTime, const mat4& cameraTransform);
	void Draw() const;

protected:
	struct Particle* m_particles;
	uint m_firstDead;
	size_t m_maxParticles;
	uint m_vao, m_vbo, m_ibo;
	struct ParticleVertex* m_vertexData;

	vec3 m_position;

	float m_emitTimer;
	float m_emitRate;

	float m_lifespanMin;
	float m_lifespanMax;

	float m_velocityMin;
	float m_velocityMax;

	float m_startSize;
	float m_endSize;

	vec4 m_startColour;
	vec4 m_endColour;
};

