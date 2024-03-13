#pragma once
#include "utils.h"
#include "SpriteManager.h"
#include "GameConsts.h"
#include <iostream>


class Player
{
public:
	Player(const Point2f& pos, const std::string& filePath, const Vector2f& velocity);
	~Player();

	void Draw() const;
	void Update(float elapsedSec);
	
	void SetIsAlive(bool myBool);
	void MoveInput(float elapsedSec);
	void Jump(const SDL_KeyboardEvent& e);
	void Dash(const SDL_KeyboardEvent& e);
	void Attack(const SDL_MouseButtonEvent& e);

	int GetNrLives();

private:
	//CONSTANTS
	const Color4f	COL_COLOR{ 0.f, 1.f, 0.f, 1.f };

	//Members
	bool m_isOnGround;
	bool m_isAlive;
	bool m_isFlipped;
	int	 m_NrLives;


	Vector2f	m_Velocity;
	Sprite*		m_Spritesheet3x5;
	Sprite*		m_Spritesheet4x1;
	Rectf		m_Collider;
	Point2f		m_Position;

	Circlef		m_AttackRange;
};

