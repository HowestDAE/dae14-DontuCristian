#include "pch.h"
#include "KillZone.h"

KillZone::KillZone(const std::string& textPath, const Vector2f& pos, int rows, int columns, float frameDelay):
	DMGZone(textPath,pos,rows,columns,frameDelay)
{
}

KillZone::~KillZone()
{
}

void KillZone::Update(float elapsedSec)
{
	m_Sprite->Update(elapsedSec, m_Pos);
}

void KillZone::Draw() const
{
	m_Sprite->Draw();

	utils::SetColor(Color4f{ 1.f,0.f,0.f,1.f });
	utils::DrawRect(m_Collider);
}

Rectf KillZone::GetCollider() const
{
	return m_Collider;
}
