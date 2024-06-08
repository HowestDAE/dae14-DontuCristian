#include "pch.h"
#include "CheckPoint.h"

CheckPoint::CheckPoint(const std::string& textPath, const Vector2f& pos, int rows, int columns, float frameDelay) :
	m_Pos		{ pos },
	m_Collider	{ pos.x - 15.f, pos.y - 15.f, 30.f, 30.f},
	m_isActive	{ false }
{
	m_Sprite = new Sprite{textPath,pos,rows,columns,frameDelay};
}

CheckPoint::~CheckPoint()
{
	delete m_Sprite;
}

void CheckPoint::Update(float elapsedSec)
{
	m_Sprite->Update(elapsedSec, m_Pos);
}

void CheckPoint::Draw()
{
	m_Sprite->Draw();

	if (m_isActive)
	{
		utils::SetColor(Color4f{1.f,0.f,0.f,1.f});
	}
	else
	{
		utils::SetColor(Color4f{ 0.f,0.f,1.f,1.f });
	}
	utils::DrawRect(m_Collider);
}

Rectf CheckPoint::GetCollider() const
{
	return m_Collider;
}

Vector2f CheckPoint::GetPosition() const
{
	return m_Pos;
}

bool CheckPoint::GetIsActive() const
{
	return m_isActive;
}

void CheckPoint::SetActive(bool myBool)
{
	m_isActive = myBool;
}

