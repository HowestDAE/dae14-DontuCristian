#pragma once
#include "utils.h"
#include "Sprite.h"
#include "GameVars.h"
#include "Collisions.h"
#include <iostream>

class Entity
{
public:
	Entity(const Point2f& pos, float speed, const std::string& filePath,
		int rows = { 8 }, int columns = { 5 }, float frameDelay = { 0.15f });
	~Entity();

	void Draw() const;
	void Update(float elapsedSec);

	void SetVelocity(Vector2f velocity);
	void SetPosition(Vector2f velocity);
	void SetCollider(Rectf velocity);
	void SetIsOnround();

	Vector2f GetPosition();
	Vector2f GetVelocity();
	Rectf	 GetCollider();


private:
	void ChangeAnimation();
	void ChangeStates();

	//CONSTANTS
	const Color4f	COL_COLOR{ 0.f, 1.f, 0.f, 1.f };
	const float DASH_SPEED = { 10.f };


	//Members
	bool m_isOnGround;
	bool m_WallHit;
	bool m_isAlive;
	bool m_isFlipped;
	float m_Speed;


	Vector2f		m_Velocity;
	Sprite*			m_Spritesheet;
	PlayerState		m_EntityState;
	Rectf			m_Collider;
	Vector2f		m_Position;
};

