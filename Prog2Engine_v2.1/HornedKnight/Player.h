#pragma once
#include "utils.h"
#include "Sprite.h"
#include "Level.h"
#include "GameVars.h"
#include "ParticleManager.h"
#include "Camera.h"
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
	takeDMG,
	fall
};
class Player
{
public:

	Player(const Vector2f& pos, const std::string& filePath,
		int rows = { 8 }, int columns = { 5 }, float frameDelay = { 0.15f });

	Player(const Player& obj) = delete;
	void operator=(const Player&) = delete;
	Player(const Player&& obj) = delete;
	void operator=(const Player&&) = delete;

	~Player();

	void Draw() const;
	void Update(float elapsedSec);

	void SetIsAlive(bool myBool);

	void Dash(const SDL_KeyboardEvent& e = {});
	void Attack(const SDL_MouseButtonEvent& e = {});

	Vector2f GetPosition() const;
	Vector2f GetVelocity() const;
	
	static void SetNrLives(int lives);
	static int GetNrLives();
private:

	void HandleCollision(float elapsedSec, const std::vector<std::vector<Point2f>>& polysVector);
	void HandleCollision(float elapsedSec, const std::vector<Platform*>& platformsVector);
	void HandleCollision(float elapsedSec, const std::vector<Enemy*>& enemyVector);
	void HandleCollision(float elapsedSec, const std::vector<DMGZone*> dmgZoneVector);


	void ChangeAnimation();
	void MoveInput(float& elapsedSec);
	void ChangeStates();

	//Static members
	static int	m_NrLives;


	//CONSTANTS
	const Color4f	COL_COLOR		{ 0.f, 1.f, 0.f, 1.f };
	const float		DASH_SPEED		{ 10.f };
	const float		SPEED			{ 90.f };
	const float     JUMP_PWR		{ 250.f };


	//Members
	float m_DMG_AccumulatedTime     { 0.f };

	bool m_isOnGround;
	bool m_WallHit;
	bool m_isAlive;
	bool m_isFlipped;

	float m_DashAngle = { 0.f };

	Rectf			m_Collider;
	Vector2f		m_Position;
	Vector2f		m_Velocity;

	Sprite*			m_Spritesheet;
	PlayerState		m_PlayerState;

	Circlef			m_AttackRange;
};

