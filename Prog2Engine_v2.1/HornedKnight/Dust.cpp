#include "pch.h"
#include "Dust.h"

Dust::Dust(const Vector2f& pos):
	Particle(pos, Vector2f{ float((rand() % 120) - 60),float(rand() % 60) })
{
}
Dust::~Dust()
{
}

void Dust::Update(float elapsedSec)
{
	 if(m_AccumulatedTime < m_AliveTime)
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
	else if(m_AccumulatedTime > m_AliveTime && m_AccumulatedTime<m_FadeOutTime+m_AliveTime)
	{
		 m_AccumulatedTime += elapsedSec;
		 std::cout << m_Opacity << "\n";
		 m_Opacity -= 0.05f;
	}
	 else
	 {
		 Destroy();
	 }
}
void Dust::Draw() const
{
	utils::SetColor(Color4f{0.8f,0.8f,0.8f,m_Opacity});
	utils::FillEllipse(m_Position.ToPoint2f(), 9.f, 9.f);
}

void Dust::Emit(const Vector2f& pos)
{
	m_AccumulatedTime = 0.f;
	m_Opacity = 1.f;
	m_Position = pos;
	m_Velocity = Vector2f{ float((rand() % 60) - 30),float(rand() % 10 + 40) };
	m_isDestroyed = false;
}

void Dust::Destroy()
{
	m_Position = Vector2f{ -100.f,-100.f };
	m_Velocity = Vector2f{ 0.f,0.f };
	m_isDestroyed = true;
}

