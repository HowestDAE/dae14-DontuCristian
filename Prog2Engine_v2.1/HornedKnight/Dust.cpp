#include "pch.h"
#include "Dust.h"

int Dust::m_DustPartCount = {};

Dust::Dust(const Vector2f& pos):
	Particle(pos, Vector2f{ float((rand() % 30) - 15),float(rand() % 10 + 20) })
{
	m_AccumulatedTime = 0.f;
	m_Opacity = 1.f;
	m_DustPartCount++;
}
Dust::~Dust()
{
	m_DustPartCount--;
}

void Dust::Update(float elapsedSec)
{
	 if(m_AccumulatedTime < ALIVE_TIME)
	 {
		m_AccumulatedTime += elapsedSec;
		if (m_Velocity.x > 0.f)
			m_Velocity.x -= 0.1f;
		else if (m_Velocity.x < 0.f)
			m_Velocity.x += 0.1f;
		if(m_Velocity.y > 0.f)
			m_Velocity.y -= (rand()%15)/10.f;

		m_Position += m_Velocity * elapsedSec;
	 }
	 else if(m_AccumulatedTime > ALIVE_TIME && m_AccumulatedTime<FADEOUT_TIME + ALIVE_TIME)
	 {
	 	 m_AccumulatedTime += elapsedSec;
	 	 m_Opacity -= 0.05f;
	 }
	 else
	 {
		 m_isDestroyed = true;
	 }
}
void Dust::Draw() const
{
	utils::SetColor(Color4f{0.8f,0.8f,0.8f,m_Opacity});
	utils::FillRect(m_Position.ToPoint2f() - Vector2f{ 2.f, 1.f }, 4.f, 2.f);
	utils::FillRect(m_Position.ToPoint2f() - Vector2f{ 1.f, 2.f }, 2.f, 4.f);
}

