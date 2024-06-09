#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(const std::string& textPath, const Vector2f& startPos, const Vector2f& endPos, const EnemyType& type,
	float colliderWidth, float colliderHeight, int rows, int columns, float frameDelay):
	m_StartPos	{startPos},
	m_Pos		{startPos},
	m_EndPos	{endPos},
	m_Type		{type},
	m_isFlipped	{false},
	m_Collider	{startPos.x - colliderWidth/2, startPos.y - colliderHeight/2,
	             colliderWidth,colliderHeight},
	m_ResetAnimation	{false}
{
	if (type == EnemyType::ranged)
	{
		m_State = EnemyStates::idle;
	}
	else
	{
		m_State = EnemyStates::run;
	}
	m_Spritesheet = new Sprite{textPath,startPos,rows,columns,frameDelay};

	m_Velocity = m_EndPos - m_StartPos;
	m_Velocity = m_Velocity.Normalized() * SPEED;

	m_Emitter = new BulletEmitter{m_Pos, Vector2f{-1.f,0.f},200.f,0.f};
}
Enemy::~Enemy()
{
	delete m_Spritesheet;
	m_Spritesheet = nullptr;
	delete m_Emitter;
	m_Emitter = nullptr;
}

void Enemy::Draw() const
{
	m_Spritesheet->Draw();

}
void Enemy::Update(float elapsedSec)
{	
	m_Collider.left = m_Pos.x - m_Collider.width / 2;
	m_Collider.bottom = m_Pos.y - m_Collider.height / 2;

	m_Spritesheet->SetFrameDelay(0.1f);
	m_Spritesheet->SetIsFlipped(m_isFlipped);

	switch (m_State)
	{
	case EnemyStates::run:
		if (m_Type == EnemyType::bat || 
			m_Type == EnemyType::normal)
		{
			m_ResetAnimation = false;
			ChangeAnimation();

			m_isFlipped = m_Velocity.x > 0 ? true : false;
			m_Spritesheet->Update(elapsedSec, m_Pos);
			Move(elapsedSec);
		}
		break;
	case EnemyStates::dead:
	{
		ChangeAnimation();
		if (!m_ResetAnimation)
		{
			m_Spritesheet->ResetAnim();
			m_ResetAnimation = true;
		}
		int frame{ m_Spritesheet->GetColIdx() };
		if (m_Spritesheet->GetColIdx() != m_Spritesheet->GetColNr() - 1)
		{
			m_Spritesheet->Update(elapsedSec, m_Pos);
		}
	}
		break;
	case EnemyStates::idle:
		ChangeAnimation();
		if (m_Type == EnemyType::ranged)
		{
			m_AccumulatedTime += elapsedSec;
			if (m_AccumulatedTime >= STATE_TIME)
			{
				m_State = EnemyStates::attack;
				m_AccumulatedTime -= STATE_TIME;
			}
		}
		m_ResetAnimation = false;
		m_Spritesheet->SetFrameDelay(0.2f);
		m_Spritesheet->Update(elapsedSec, m_Pos);
		break;
	case EnemyStates::attack:
		if (!m_ResetAnimation)
		{
			m_Spritesheet->ResetAnim();
			m_ResetAnimation = true;
		}
		ChangeAnimation();
		if (m_Spritesheet->GetColIdx() != m_Spritesheet->GetColNr() - 1)
		{
			m_Spritesheet->Update(elapsedSec, m_Pos);
		}
		else if (m_Spritesheet->GetColIdx() == m_Spritesheet->GetColNr() - 1)
		{
			m_Emitter->Shoot("FireBullet.png");
			m_State = EnemyStates::idle;
		}
		break;
	}
}
void Enemy::Move(float elapsedSec)
{
	float xSpeed{ fabs(m_Velocity.x) };
	float ySpeed{ fabs(m_Velocity.y) };


	m_Pos.x += m_Velocity.x * elapsedSec;

	if (m_Type == EnemyType::bat)
	{
		m_Pos.y += m_Velocity.y * elapsedSec;
	}

	//Move the Enemy left and right
	if (m_StartPos.x < m_EndPos.x)
	{
		if (m_Pos.x >= m_EndPos.x)
		{
			m_Velocity.x = -xSpeed;
		}
		if (m_Pos.x < m_StartPos.x)
		{
			m_Velocity.x = xSpeed;
		}
	}
	else
	{
		if (m_Pos.x <= m_EndPos.x)
		{
			m_Velocity.x = xSpeed;
		}
		if (m_Pos.x > m_StartPos.x)
		{
			m_Velocity.x = -xSpeed;
		}
	}

	//Move the Enemy up and down
	if (m_StartPos.y < m_EndPos.y)
	{
		if (m_Pos.y >= m_EndPos.y)
		{
			m_Velocity.y = -ySpeed;
		}
		if (m_Pos.y < m_StartPos.y)
		{
			m_Velocity.y = ySpeed;
		}
	}
	else
	{
		if (m_Pos.y <= m_EndPos.y)
		{
			m_Velocity.y = ySpeed;
		}
		if (m_Pos.y > m_StartPos.y)
		{
			m_Velocity.y = -ySpeed;
		}
	}
}
void Enemy::ChangeAnimation()
{
	m_Spritesheet->SetAnimation(int(m_State));
}

void Enemy::SetState(EnemyStates state)
{
	m_State = state;
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
	return m_State;
}

EnemyType Enemy::GetType() const
{
	return m_Type;
}

