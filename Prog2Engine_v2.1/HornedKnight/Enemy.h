#pragma once
#include "Sprite.h"
#include "utils.h"

class Entity
{public:
	void Draw() const;
	void Update(float elapsedSec);

	void SetIsAlive(bool myBool);

	void ChangeAnimation();
	Point2f GetPosition();
private:
	//CONSTANTS
	const Color4f	COL_COLOR{ 0.f, 1.f, 0.f, 1.f };

	//Members
	bool m_isOnGround;
	bool m_isAlive;
	bool m_isFlipped;
	float m_Speed;


	Vector2f		m_Velocity;
	Sprite*			m_Spritesheet;
	Rectf			m_Collider;
	Vector2f		m_Position;

	Rectf			m_AttackRange;

};

