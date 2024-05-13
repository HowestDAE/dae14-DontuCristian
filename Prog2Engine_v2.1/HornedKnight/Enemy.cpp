#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(const std::string& textPath, const Vector2f& startPos, float colliderWidth, float colliderHeight,
	         float travelDist, int rows, int columns, float frameDelay):
	m_StartPos	{startPos},
	m_Pos		{startPos},
	TRAVEL_DIST {travelDist},
	m_EnemyState{EnemyStates::run},
	m_Velocity  {SPEED,SPEED},
	m_isFlipped	{false},
	m_Collider	{startPos.x - colliderWidth/2, startPos.y - colliderHeight/2,
	             colliderWidth,colliderHeight}
{
	m_Spritesheet = new Sprite{textPath,startPos,rows,columns,frameDelay};
}
Enemy::~Enemy()
{
	delete m_Spritesheet;
}

void Enemy::Draw() const
{
	m_Spritesheet->Draw();

	utils::SetColor(Color4f{ 1.f,0.f,0.f,1.f });
	utils::DrawRect(m_Collider);
}
void Enemy::Update(float elapsedSec)
{		
	ChangeAnimation();

	m_Collider.left = m_Pos.x - m_Collider.width / 2;
	m_Collider.bottom = m_Pos.y - m_Collider.height / 2;

	switch (m_EnemyState)
	{
	case EnemyStates::run:
		m_Spritesheet->SetIsFlipped(m_isFlipped);

		m_isFlipped = m_Velocity.x < 0 ? true : false;
		m_Spritesheet->Update(elapsedSec, m_Pos);
		Move(elapsedSec);
		break;
	case EnemyStates::dead:

		if (m_Spritesheet->GetColIdx() != m_Spritesheet->GetColNr()-1)
		{
			m_Spritesheet->Update(elapsedSec, m_Pos);
		}
		break;
	}
}
void Enemy::Move(float elapsedSec)
{
	m_Pos.x += m_Velocity.x * elapsedSec;

	//Move the Enemy left and right
	if (m_Pos.x >= m_StartPos.x + TRAVEL_DIST)
	{
		m_Velocity.x = -SPEED;
	}
	if (m_Pos.x < m_StartPos.x)
	{
		m_Velocity.x = SPEED;
	}

	//Move the Enemy up and down
	if (m_Pos.y >= m_StartPos.y + TRAVEL_DIST)
	{
		m_Velocity.y = -SPEED;
	}
	if (m_Pos.y < m_StartPos.y)
	{
		m_Velocity.y = SPEED;
	}
}
void Enemy::SetIsAlive(bool myBool)
{
	m_EnemyState = EnemyStates::dead;
}
void Enemy::ChangeAnimation()
{
	m_Spritesheet->SetAnimation(int(m_EnemyState));
}

Vector2f Enemy::GetPosition() const
{
	return m_Pos;
}

Rectf Enemy::GetCollider() const
{
	return m_Collider;
}

EnemyStates Enemy::GetState() const
{
	return m_EnemyState;
}

