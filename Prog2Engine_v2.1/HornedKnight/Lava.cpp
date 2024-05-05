#include "pch.h"
#include "Lava.h"

Lava::Lava(const Vector2f& pos) :
	Particle(pos, Vector2f{ 0.f,0.f }),
	m_DestroyRayY{ -1.f },
	m_Size{15.f}
{
}

Lava::~Lava()
{
}

void Lava::Update(float elapsedSec,float targetY)
{
	float targetYVel{ targetY - m_Position.y };
	float maxDist{150.f};//max dist from the emition point
	m_Size -= fabs(targetYVel / maxDist);
	if (m_Size < 3.f)
	{
		m_Position.y = targetY;
		m_Size = 15.f;
	}
	else
	{
		if (targetYVel > 0.f)
		{
			m_Position.y += (m_Velocity.y + targetYVel / fabs(targetY)) * elapsedSec;
		}
		else
		{
			m_Position.y += (fabs(m_Velocity.y) + targetYVel / fabs(targetY)) * elapsedSec;
		}
	}
}

void Lava::Draw() const
{
	utils::SetColor(Color4f{ 1.f,0.f,0.f,1.f});
	utils::FillRect(m_Position.ToPoint2f(), m_Size, m_Size);
}

void Lava::Emit(Vector2f pos)
{
	m_Velocity = Vector2f{ 0.f,-float(rand() % 50 + 50) };
	m_Position.x = pos.x + float(rand()%20-10);
	m_Position.y = pos.y - float(rand()%80);
	m_Size = 15.f;
	std::cout << "Wegoin";
}
