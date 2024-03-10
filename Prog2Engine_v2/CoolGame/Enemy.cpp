#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(const Point2f& pos, const std::string& filePath):
	m_isAlive{ true }
{
	m_Position = pos;
	m_AttackRange = Circlef{ pos,15 };
	m_PlSpritesheet = new	Texture{ filePath };
}

Enemy::~Enemy()
{
}

void Enemy::Draw() const
{
}

void Enemy::Update()
{
}

void Enemy::SetIsAlive(bool myBool)
{
	m_isAlive = myBool;
}
