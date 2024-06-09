#include "pch.h"
#include "DMGZone.h"

DMGZone::DMGZone(const std::string& textPath, const Vector2f& pos, int rows, int columns, float frameDelay):
	m_Pos{pos}
{
	m_Sprite = new Sprite{ textPath,pos,rows,columns,frameDelay};
	m_Collider = Rectf{m_Pos.x - float(m_Sprite->GetFrameWidth()/2),m_Pos.y-float(m_Sprite->GetFrameHeight()/2),
								 float(m_Sprite->GetFrameWidth()),float(m_Sprite->GetFrameHeight())};
}

DMGZone::~DMGZone()
{
	delete m_Sprite;
	m_Sprite = nullptr;
}

void DMGZone::Update(float elapsedSec)
{
	m_Sprite->Update(elapsedSec, m_Pos);
}

void DMGZone::Draw() const
{
	m_Sprite->Draw();
}

Rectf DMGZone::GetCollider() const
{
	return m_Collider;
}
