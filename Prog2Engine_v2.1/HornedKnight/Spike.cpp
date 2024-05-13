#include "pch.h"
#include "Spike.h"

Spike::Spike(const std::string& textPath, const Vector2f& pos, int rows, int columns, float frameDelay) :
	DMGZone(textPath,pos,rows,columns,frameDelay)
{
}

Spike::~Spike()
{
}
void Spike::Update(float elapsedSec)
{
	m_AccumulatedTime += elapsedSec;
	if (m_AccumulatedTime >= 3.f)
	{
		m_Sprite->SetAnimation(1);
		if (m_Sprite->GetColIdx() == 4)
		{
			m_Sprite->ResetAnim();
			m_Sprite->SetAnimation(0);
			m_AccumulatedTime = 0.f;
		}

		m_Sprite->Update(elapsedSec, m_Pos);
	}
}

void Spike::Draw() const
{
	m_Sprite->Draw();

	utils::SetColor(Color4f{ 1.f,0.f,0.f,1.f });
	utils::DrawRect(m_Collider);
}
