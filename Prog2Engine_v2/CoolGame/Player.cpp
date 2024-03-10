#include "pch.h"
#include "Player.h"

Player::Player(const Point2f& pos, const std::string& filePath):
	m_isAlive{true},
	m_NrLives{7}
{
	m_Position = pos;
	m_AttackRange = Circlef{ pos,15 };
	m_PlSpritesheet = new	Texture{filePath};
}

Player::~Player()
{
	delete m_PlSpritesheet;
}

void Player::Draw() const
{
}

void Player::Update()
{

}

void Player::SetIsAlive(bool myBool)
{
	m_isAlive = myBool;
}

int Player::GetNrLives()
{
	return m_NrLives;
}
