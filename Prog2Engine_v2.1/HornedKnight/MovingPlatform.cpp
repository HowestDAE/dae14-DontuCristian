#include "pch.h"
#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(const std::string& textPath, const Vector2f& startPos,float dist,float period):
	Platform(textPath,startPos),
	TRAVEL_DIST{dist},
	m_TickCounter{0.f},
	PERIOD{period},
	m_StartPos{startPos},
	m_XDeviation{0.f}
{
	m_Collider = Rectf{ startPos.x - m_Sprite->GetFrameWidth() / 2.f, startPos.y - m_Sprite->GetFrameHeight() / 2.f,
							float(m_Sprite->GetFrameWidth() - 4.f), float(m_Sprite->GetFrameHeight()) };
}

void MovingPlatform::Update(float elapsedSec)
{
	m_TickCounter += elapsedSec;

	float wavePorgression{m_TickCounter/PERIOD};
	float xDeviation{};

	xDeviation = TRAVEL_DIST * float(cos(2 * M_PI * wavePorgression - M_PI)) + TRAVEL_DIST;
	
	m_VelocityX = (xDeviation - m_XDeviation)/elapsedSec;

	m_XDeviation = xDeviation;

	m_Pos.x = m_StartPos.x + xDeviation;

	m_Collider.left = m_Pos.x - m_Collider.width / 2 - 1.f;

	m_Sprite->Update(elapsedSec, m_Pos);
}
