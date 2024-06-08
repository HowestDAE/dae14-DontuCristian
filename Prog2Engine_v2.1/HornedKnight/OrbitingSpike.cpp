#include "pch.h"
#include "OrbitingSpike.h"

OrbitingSpike::OrbitingSpike(const std::string& textPath, const Rectf& targetRect, bool clockwise,
							 int rows, int columns, float frameDelay):
	Spike(textPath, Vector2f{targetRect.left,targetRect.bottom},rows,columns,frameDelay),
	m_TargetRect {targetRect},
	m_Clockwise  {clockwise}
{
	m_Pos.x -= m_Collider.width  / 2;
	m_Pos.y -= m_Collider.height / 2;

	m_Collider.left   = m_Pos.x - m_Collider.width  / 2;
	m_Collider.bottom = m_Pos.y - m_Collider.height / 2;

	if (m_Clockwise)
	{
		m_Velocity = Vector2f{0.f,SPEED};
	}
	else
	{
		m_Velocity = Vector2f{ SPEED,0.f };
	}
}

OrbitingSpike::~OrbitingSpike()
{
}

void OrbitingSpike::Update(float elapsedSec)
{
	m_Pos += m_Velocity * elapsedSec;

	m_Collider.left = m_Pos.x - m_Collider.width / 2;
	m_Collider.bottom = m_Pos.y - m_Collider.height / 2;

	Vector2f bottomLeft		{ m_Collider.left, m_Collider.bottom };
	Vector2f topLeft		{ m_Collider.left, m_Collider.bottom + m_Collider.height };
	Vector2f topRight		{ m_Collider.left + m_Collider.width, m_Collider.bottom + m_Collider.height };
	Vector2f bottomRight	{ m_Collider.left + m_Collider.width, m_Collider.bottom };

	Vector2f targetBottomLeft	{ m_TargetRect.left, m_TargetRect.bottom };
	Vector2f targetTopLeft		{ m_TargetRect.left, m_TargetRect.bottom + m_TargetRect.height };
	Vector2f targetTopRight		{ m_TargetRect.left + m_TargetRect.width, m_TargetRect.bottom + m_TargetRect.height };
	Vector2f targetBottomRight	{ m_TargetRect.left + m_TargetRect.width, m_TargetRect.bottom };

	m_Sprite->Update(elapsedSec,m_Pos);

	if (m_Clockwise)
	{
		if ((bottomRight.x == targetTopLeft.x) && (bottomRight.y >= targetTopLeft.y))
		{
			m_Velocity = Vector2f{ SPEED,0.f };
			m_Pos.y += targetTopLeft.y - bottomRight.y;
		}
		if ((bottomLeft.x >= targetTopRight.x)&&(bottomLeft.y == targetTopRight.y))
		{
			m_Velocity = Vector2f{ 0.f, -SPEED };
			m_Pos.x += targetTopRight.x - bottomLeft.x;
		}
		if ((topLeft.y <= targetBottomRight.y) && (topLeft.x == targetBottomRight.x))
		{
			m_Velocity = Vector2f{ -SPEED , 0.f };
			m_Pos.y += targetBottomRight.y - topLeft.y;
		}
		if ((topRight.x <= targetBottomLeft.x) && (topRight.y == targetBottomLeft.y))
		{
			m_Pos.x += targetBottomLeft.x - topRight.x;
			m_Velocity = Vector2f{ 0.f,SPEED };
		}
	}
	else if(!m_Clockwise)
	{
		if ((topLeft.x >= targetBottomRight.x) && (topLeft.y == targetBottomRight.y))
		{
			m_Velocity = Vector2f{ 0.f, SPEED };
			m_Pos.x += targetBottomRight.x - topLeft.x;
		}
		if ((bottomLeft.y >= targetTopRight.y) && (bottomLeft.x == targetTopRight.x))
		{
			m_Velocity = Vector2f{ -SPEED, 0.f };
			m_Pos.y += targetTopRight.y - bottomLeft.y;
		}
		if ((bottomRight.x <= targetTopLeft.x) && (bottomRight.y == targetTopLeft.y))
		{
			m_Velocity = Vector2f{ 0.f, -SPEED };
			m_Pos.x += targetTopLeft.x - bottomRight.x;
		}
		if ((topRight.y <= targetBottomLeft.y) && (topRight.x == targetBottomLeft.x))
		{
			m_Pos.y += targetBottomLeft.y - topRight.y;
			m_Velocity = Vector2f{ SPEED, 0.f };
		}
	}
}
