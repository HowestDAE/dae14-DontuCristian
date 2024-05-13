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
}
void Platform::Update(float elapsedSec)
{
	m_Sprite->Update(elapsedSec, m_Pos);
}
void Platform::Draw()const
{
	m_Sprite->Draw();
	utils::SetColor(Color4f{ 1.f,0.f,0.f,1.f });
	utils::DrawRect(m_Collider);
}

float Platform::GetVelocityX()
{
	return m_VelocityX;
}

Rectf Platform::GetCollider()
{
	return m_Collider;
}
