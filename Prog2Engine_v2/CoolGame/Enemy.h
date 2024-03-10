#pragma once
#include "Texture.h"

enum class EnemyTypes
{
	skelly,
	worm,
	spikey,
	bat

};

class Enemy
{
public:

	Enemy(const Point2f& pos, const std::string& filePath);
	~Enemy();

	void Draw() const;

	void Update();

	void SetIsAlive(bool myBool);

private:
	bool m_isAlive;

	Texture* m_PlSpritesheet;
	Rectf m_Collider;
	Point2f m_Position;

	Circlef m_AttackRange;
};

