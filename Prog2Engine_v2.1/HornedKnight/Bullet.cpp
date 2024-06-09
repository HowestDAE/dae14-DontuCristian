#include "pch.h"
#include "Bullet.h"

const float Bullet::SPEED = 40.f;

Bullet::Bullet(const std::string& textPath, const Vector2f& pos, const Vector2f& direction, float destructDist,
	int rows, int columns, float frameDelay):
	DESTRUCT_TIME{ destructDist /SPEED},
	m_Pos{pos},
	m_AccumulatedTime{0.f},
	m_isDestroyed{ false },
	m_isFlipped{false}
{
	m_Sprite = new Sprite{textPath, pos, rows, columns,frameDelay};
	m_Velocity = direction * SPEED;

	m_Collider = Rectf{ pos.x - m_Sprite->GetFrameWidth() / 2.f,pos.y - m_Sprite->GetFrameHeight() / 2.f,
		float(m_Sprite->GetFrameWidth()), float(m_Sprite->GetFrameHeight()) };
}

Bullet::~Bullet()
{
	delete m_Sprite;
}

void Bullet::Update(float elapsedSec)
{
	m_AccumulatedTime += elapsedSec;

	if (m_AccumulatedTime >= DESTRUCT_TIME)
	{
		m_isDestroyed = true;
	}

	if (!m_isDestroyed)
	{
		m_isFlipped = m_Velocity.x > 0 ? false : true ;
		m_Sprite->SetIsFlipped(m_isFlipped);

		m_Pos += m_Velocity * elapsedSec;
		m_Sprite->Update(elapsedSec, m_Pos);

		m_Collider.left = m_Pos.x - m_Sprite->GetFrameWidth() / 2;
		m_Collider.bottom = m_Pos.y - m_Sprite->GetFrameHeight() / 2;

	}
}
void Bullet::Draw() const
{
	m_Sprite->Draw();
}

bool Bullet::GetIsDestroyed()
{
	return m_isDestroyed;
}

Rectf Bullet::GetCollider()
{
	return m_Collider;
}

Vector2f Bullet::GetPosition()
{
	return m_Pos;
}

void Bullet::Destroy()
{
	m_isDestroyed = true;
}
