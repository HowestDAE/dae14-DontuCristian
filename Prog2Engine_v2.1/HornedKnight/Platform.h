#pragma once
#include "utils.h"
#include "Sprite.h"
class Platform
{
public:														//for the sprite animations |
															//	                        v
															// (																)
	Platform(const std::string& textPath, const Vector2f& pos, int rows = { 1 }, int columns = { 1 }, float frameDelay = { 0.f });
	virtual ~Platform();

	virtual void Update(float elapsedSec);

	void Draw() const;

	float GetVelocityX();
	Rectf GetCollider();
protected:

	//Member varibles
	float m_VelocityX;

	Rectf m_Collider;
	Vector2f m_Pos;
	
	Sprite* m_Sprite;
};

