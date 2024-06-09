#pragma once
#include "Sprite.h"
#include "ParticleManager.h"
#include "BulletEmitter.h"
#include "utils.h"

enum class EnemyType
{
	bat,
	ranged,
	normal
};

enum class EnemyStates
{
	run,
	idle,
	dead,
	attack
};

class Enemy
{public:
	Enemy(const std::string& textPath, const Vector2f& startPos,const Vector2f& endPos,const EnemyType& type ,
		float colliderWidth, float colliderHeight, int rows, int columns, float frameDelay);

	//Rule of 5
	void operator=(const Enemy&) = delete;
	void operator=(const Enemy&&) = delete;

	Enemy(const Enemy& obj) = delete;
	Enemy(const Enemy&& obj) = delete;
	~Enemy();


	void Draw() const;
	
	virtual void Update(float elapsedSec);

	void Move(float elapsedSec);

	void ChangeAnimation();
	void SetState(EnemyStates state);

	Vector2f GetPosition() const;
	Rectf	 GetCollider() const;
	EnemyStates GetState() const;
	EnemyType	 GetType() const;

private:
	//CONSTANTS
	const float		SPEED		{30.f};
	const float		STATE_TIME	{2.f};

	//Members
	bool	m_isFlipped;
	bool	m_ResetAnimation;

	float	m_AccumulatedTime{};

	EnemyStates m_State;
	EnemyType	m_Type;

	Vector2f	m_Velocity;
	Sprite*		m_Spritesheet;
	Rectf		m_Collider;
	Vector2f	m_StartPos;
	Vector2f	m_EndPos;
	Vector2f	m_Pos;

	BulletEmitter* m_Emitter;
};

