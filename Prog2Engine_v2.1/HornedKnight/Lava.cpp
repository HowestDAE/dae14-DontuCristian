#include "pch.h"
#include "Lava.h"

const float Lava::MAX_SIZE = { 4.f };
const float Lava::MAX_DIST = { 60.f };

int Lava::m_LavaPartCount = {};

Lava::Lava(const Vector2f& pos) :
	Particle(pos, Vector2f{ 0.f,-float(rand() % 30 + 30) }),
	m_DestroyRayY{ -1.f }
{
	m_Size = MAX_SIZE ;
	m_LavaPartCount++;
}

Lava::~Lava()
{
	m_LavaPartCount--;
}

void Lava::Update(float elapsedSec,float targetY)
{
	float targetYVel{ targetY - m_Position.y };
	float yVel{ m_Velocity.y + targetYVel / fabs(targetY) };

	m_Size -= fabs(targetYVel / MAX_DIST);

	if (m_Size < 0.3f)
	{
		m_Position.y = targetY;
		m_Size = MAX_SIZE;
	}
	else
	{
		if (targetYVel > 0.f)
		{
			m_Position.y += yVel * elapsedSec;
		}
		else
		{
			yVel = -m_Velocity.y + targetYVel / fabs(targetY);

			m_Position.y += yVel * elapsedSec;
		}
	}
}

void Lava::Draw() const
{
	utils::SetColor(Color4f{ 1.f,0.f,0.f,1.f});
	utils::FillRect(m_Position.ToPoint2f(), m_Size, m_Size);
}