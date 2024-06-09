#pragma once
#include "utils.h"
#include "Sprite.h"

class Bullet
{
public:
	
	Bullet(const std::string& textPath, const Vector2f& pos, const Vector2f& direction, float destructDist,
		int rows, int columns, float frameDelay);

	//Rule of 5
	void operator=(const Bullet&) = delete;
	void operator=(const Bullet&&) = delete;

	Bullet(const Bullet& obj) = delete;
	Bullet(const Bullet&& obj) = delete;

	~Bullet();

	//Member functions
	void Update(float elapsedSec);
	void Draw() const;

	bool GetIsDestroyed();
	Rectf GetCollider();
	Vector2f GetPosition();

	void Destroy();

private:
	//CONSTANTS
	const float DESTRUCT_TIME;

	//static members
	static const float SPEED;



	//Datamembers
	float m_AccumulatedTime;
	bool m_isDestroyed;
	bool m_isFlipped;

	Vector2f	m_Pos;
	Vector2f	m_Velocity;
	Rectf		m_Collider;
	Sprite*		m_Sprite;
};

