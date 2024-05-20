#include "pch.h"
#include "RotatingSpike.h"

RotatingSpike::RotatingSpike(const std::string& textPath, const Vector2f& pos,
	int rows, int columns, float frameDelay) : Spike(textPath, pos, rows, columns, frameDelay),
	m_Angle{ 0.f }
{
}

RotatingSpike::~RotatingSpike()
{
}

void RotatingSpike::Update(float elapsedSec)
{
	m_Angle += elapsedSec;
}

void RotatingSpike::Draw() const
{
	glPushMatrix();
	{

		glRotatef(m_Angle,0.f, 0.f, 1.f);
		glTranslatef(0.f, -30.f, 0.f);

		utils::FillEllipse(m_Pos.ToPoint2f(), 10.f, 10.f);
	}
	glPopMatrix();
}
