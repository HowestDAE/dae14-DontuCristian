#include "pch.h"
#include "Particle.h"

int Particle::m_ParticleCount = {};

Particle::Particle(const Vector2f&  pos,const Vector2f& vel):
	m_Position{pos},
	m_Velocity{vel}
{
	m_isDestroyed = false;
	m_ParticleCount++;
}

Particle::~Particle()
{
	m_ParticleCount--;
}

void Particle::Draw() const
{
}
bool Particle::GetIsDestroyed()
{
	return m_isDestroyed;
}
void Particle::Update(float elapsedSec)
{
	m_Position += m_Velocity * elapsedSec;
}