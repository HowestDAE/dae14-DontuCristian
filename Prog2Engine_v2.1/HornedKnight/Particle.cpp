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
	//utils::FillRect(Rectf{m_Position.x-10.f,m_Position.y-10.f,20.f,20.f});
}
bool Particle::GetIsDestroyed()
{
	return m_isDestroyed;
}
void Particle::Update(float elapsedSec)
{
	m_Position += m_Velocity * elapsedSec;
}
void Particle::Update(float elapsedSec, float targetY)
{
}