#include "pch.h"
#include "Dash.h"

Dash::Dash(const Vector2f& pos):Particle{ pos,Vector2f{0.f,0.f}}
{
}

Dash::~Dash()
{
}

void Dash::Update(float elapsedSec)
{
	m_ElapsedSec = elapsedSec;
	m_Position += m_Velocity * elapsedSec;
}

void Dash::Draw() const
{
	utils::SetColor(Color4f{0.9f,0.9f,0.9f,1.f});
	utils::FillRect(m_Position.ToPoint2f(),5.f,5.f);
}

void Dash::Emit(Vector2f pos)
{
	const int pPerSec{ 3 };//particles per sec
	const float interval{ 1.f / pPerSec };//interval between particles emission

	m_AccumulatedTime += m_ElapsedSec;
	if (m_AccumulatedTime >= interval)
	{
		m_Opacity = 1.f;
		m_Position = pos;
		m_Velocity = Vector2f{ float((rand() % 30) - 15),float((rand() % 10) - 5) };
		m_isDestroyed = false;
		m_AccumulatedTime -= interval;
	}
}
