#pragma once
#include "Sprite.h"
#include "utils.h"

enum class EnemyStates
{
	run,
	dead,
	idle
};

class Enemy
{public:
	Enemy(const std::string& textPath, const Vector2f& startPos, float colliderWidth, float colliderHeight, 
		  float travelDist, int rows, int columns, float frameDelay);

	//Rule of 5
	void operator=(const Enemy&) = delete;
	void operator=(const Enemy&&) = delete;

	Enemy(const Enemy& obj) = delete;
	Enemy(const Enemy&& obj) = delete;
	~Enemy();


	void Draw() const;
	void Update(float elapsedSec);

	void Move(float elapsedSec);

	void SetIsAlive(bool myBool);

	void	 ChangeAnimation();

	Vector2f GetPosition() const;
	Rectf	 GetCollider() const;
	EnemyStates GetState() const;

private:
	//CONSTANTS
	const float		SPEED	{30.f};
	const float		TRAVEL_DIST;

	//Members
	bool	m_isFlipped;

	EnemyStates m_EnemyState;

	Vector2f	m_Velocity;
	Sprite*		m_Spritesheet;
	Rectf		m_Collider;
	Vector2f	m_StartPos;
	Vector2f	m_Pos;

};

