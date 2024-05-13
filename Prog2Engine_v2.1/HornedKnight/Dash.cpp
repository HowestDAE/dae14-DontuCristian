#include "pch.h"
#include "Dash.h"

int Dash::m_DashPartCount = {};

Dash::Dash(const Vector2f& pos):
	Particle{ pos,Vector2f{ float((rand() % 16) - 8),float((rand() % 16) - 8) }}
{
	m_DashPartCount++;
}

Dash::~Dash()
{
	m_DashPartCount--;
}

void Dash::Update(float elapsedSec)
{
	if (m_AccumulatedTime < ALIVE_TIME)
	{
		m_AccumulatedTime += elapsedSec;
		m_Position += m_Velocity * elapsedSec;
	}
	else if (m_AccumulatedTime > ALIVE_TIME && m_AccumulatedTime < FADEOUT_TIME + ALIVE_TIME)
	{
		m_AccumulatedTime += elapsedSec;
		m_Opacity -= 0.05f;
	}
	else
	{
		m_isDestroyed = true;
	}
}

void Dash::Draw() const
{
	utils::SetColor(Color4f{0.9f,0.9f,0.9f,m_Opacity});
	utils::FillRect(m_Position.ToPoint2f(),2.f,2.f);
}
