#include "pch.h"
#include "Blood.h"

Blood::Blood(const Vector2f& pos):
	Particle(pos, Vector2f{float(rand()%20-10),float(rand()%60 + 30)})
{
}

Blood::~Blood()
{
}

void Blood::Update(float elapsedSec)
{
	if (m_AccumulatedTime < ALIVE_TIME)
	{
		m_AccumulatedTime += elapsedSec;

		m_Velocity.y -= 2.f;
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
void Blood::Draw() const
{
	utils::SetColor(Color4f{1.f,0.f,0.f,m_Opacity});
	utils::FillRect(m_Position.x - 1.5f,m_Position.y-1.5f,3.f,3.f);
}
