#pragma once
#include "utils.h"
#include "Sprite.h"
#include "GameVars.h"
#include <iostream>

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
	Player(	const Point2f& pos, float speed,float jmpPower, const std::string& filePath, 
			int rows = { 8 }, int columns = { 5 }, float frameDelay = { 0.15f });
	~Player();

	void Draw() const;
	void Update(float elapsedSec);

	void SetIsAlive(bool myBool);
	void MoveInput();
	void ChangeStates();

	void Jump(const SDL_KeyboardEvent& e = {});
	void Dash(const SDL_KeyboardEvent& e = {});
	void Attack(const SDL_MouseButtonEvent& e = {});


	void ChangeAnimation();

	int GetNrLives();
	Point2f GetPosition();

private:
	//CONSTANTS
	const Color4f	COL_COLOR{ 0.f, 1.f, 0.f, 1.f };

	//Members
	bool m_isOnGround;
	bool m_isAlive;
	bool m_isFlipped;
	int	 m_NrLives;
	float m_Speed;
	float m_JmpPower;


	Vector2f		m_Velocity;
	Sprite*			m_Spritesheet8x5;
	PlayerState		m_PlayerState;
	Rectf			m_Collider;
	Point2f			m_Position;

	Circlef			m_AttackRange;
};

