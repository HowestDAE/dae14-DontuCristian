#pragma once
#include "Texture.h"

class Enemy
{
public:

	Enemy(const Point2f& pos, const std::string& filePath);
	~Enemy();

	virtual void Draw() const = 0;
	virtual void Update() = 0;

	void SetIsAlive(bool myBool);

private:
	bool m_isAlive;

	Texture* m_PlSpritesheet;
	Rectf m_Collider;
	Point2f m_Position;

	Circlef m_AttackRange;
};

