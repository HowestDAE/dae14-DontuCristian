#include "pch.h"
#include "Fireball.h"

Fireball::Fireball(const std::string& textPath, const Vector2f& startPos, int rows, int columns, float frameDelay):
	DMGZone(textPath,startPos,rows,columns,frameDelay),
	m_YDeviation{ 0.f },
	m_StartPos{startPos},
	m_TickCounter{0.f},
	TRAVEL_DIST{25.f},
	PERIOD{2.f}
{
}

Fireball::~Fireball()
{
}

void Fireball::Update(float elapsedSec)
{
	m_TickCounter += elapsedSec;

	float wavePorgression{ m_TickCounter / PERIOD };
	float yDeviation{};

	m_VelocityY = (yDeviation - m_YDeviation) / elapsedSec;

	yDeviation = TRAVEL_DIST * float(cos(2 * M_PI * wavePorgression - M_PI)) + TRAVEL_DIST;

	m_YDeviation = yDeviation;

	m_Pos.y = m_StartPos.y + yDeviation;

	m_Collider.bottom = m_Pos.y - m_Collider.height / 2;

	m_Sprite->Update(elapsedSec, m_Pos);
}

float Fireball::GetYVelocity()
{
	return m_VelocityY;
}
