#pragma once
#include "utils.h"
#include "Sprite.h"
#include "Level.h"
#include "GameVars.h"
#include <iostream>

class Collisions;

enum class PlayerState
{
	attack,
	walking,
	idle,
	dash,
	jump,
	wallSlide,
	push,
	fall
};
class Player
{
public:

	Player(const Player& obj) = delete;
	void operator=(const Player&) = delete;

	Player(const Vector2f& pos, float speed, float jmpPower, const std::string& filePath,
		int rows = { 8 }, int columns = { 5 }, float frameDelay = { 0.15f });

	~Player();

	void Draw() const;
	void Update(float elapsedSec);

	void SetIsAlive(bool myBool);

	void Jump(const SDL_KeyboardEvent& e = {});
	void Dash(const SDL_KeyboardEvent& e = {});
	void Attack(const SDL_MouseButtonEvent& e = {});

	int		 GetNrLives();
	Vector2f GetPosition();
	Vector2f GetVelocity();

private:

	void HandleCollision(float elapsedSec,std::vector<Point2f> poly);
	void ChangeAnimation();
	void MoveInput();
	void ChangeStates();

	//CONSTANTS
	const Color4f	COL_COLOR{ 0.f, 1.f, 0.f, 1.f };
	const float DASH_SPEED = { 10.f };

	float m_ElapsedSec;
	//Members
	bool m_isOnGround;
	bool m_WallHit;
	bool m_isAlive;
	bool m_isFlipped;
	int	 m_NrLives;
	float m_Speed;
	float m_JmpPower;
	float m_DashAngle = { 0.f };

	Rectf			m_Collider;
	Vector2f		m_Position;
	Vector2f		m_Velocity;

	Sprite*			m_Spritesheet;
	PlayerState		m_PlayerState;

	Circlef			m_AttackRange;
};

