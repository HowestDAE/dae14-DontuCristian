#include "pch.h"
#include "Platform.h"

Platform::Platform(const std::string& textPath, const Vector2f& pos, int rows, int columns, float frameDelay) :
	m_Pos{ pos },
	m_VelocityX{ 0.f }
{
	m_Sprite = new Sprite{textPath,pos,rows,columns,frameDelay};
}

Platform::~Platform()
{
	delete m_Sprite;
	m_Sprite = nullptr;
}
void Platform::Update(float elapsedSec)
{
}
void Platform::Draw()const
{
	m_Sprite->Draw();
}

float Platform::GetVelocityX()
{
	return m_VelocityX;
}

Rectf Platform::GetCollider()
{
	return m_Collider;
}
