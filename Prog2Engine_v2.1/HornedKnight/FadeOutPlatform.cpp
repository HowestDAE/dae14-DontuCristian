#include "pch.h"
#include "FadeOutPlatform.h"

const float FadeOutPlatform::INTERACTABLE_TIME = {1.f};
const float FadeOutPlatform::FADE_TIME =  {0.5f};
const float FadeOutPlatform::RESET_TIME = {1.5f};

FadeOutPlatform::FadeOutPlatform(const std::string& textPath, const Vector2f& pos, int rows, int columns):
	Platform(textPath, pos, rows, columns, RESET_TIME/columns),
	m_isInteractable	{ true },
	m_AccumulatedTime	{ 0.f },
	m_PresetHeight		{ pos.y },
	m_Collision			{ false }
{
	m_Collider = Rectf{ pos.x - m_Sprite->GetFrameWidth() / 2.f + 1.f, pos.y - m_Sprite->GetFrameHeight() / 2.f + 5.f,
							float(m_Sprite->GetFrameWidth()-1.f), float(m_Sprite->GetFrameHeight()-5.f) };
}
void FadeOutPlatform::Update(float elapsedSec)
{
	m_Sprite->Update(elapsedSec, m_Pos);
	m_Sprite->SetAnimation(0);

	if (m_Collision)
	{
		m_AccumulatedTime += elapsedSec;

		if (m_AccumulatedTime >= INTERACTABLE_TIME && m_AccumulatedTime < INTERACTABLE_TIME + FADE_TIME)
		{
			m_isInteractable = false;
			m_Sprite->SetAnimation(2);
		}
		else
		{
 			m_Sprite->SetAnimation(1);
		}
		if (m_AccumulatedTime >= INTERACTABLE_TIME + FADE_TIME)
		{
				m_Pos.y = -100.f;
		}

	}
	if (m_AccumulatedTime >= INTERACTABLE_TIME + FADE_TIME + RESET_TIME)
	{
		m_Sprite->ResetAnim();
		m_Pos.y = m_PresetHeight;
		m_AccumulatedTime = 0.f;
		m_Collision = false;
		m_isInteractable = true;
	}
	m_Collider.bottom = m_Pos.y - m_Collider.height / 2 + 2.5f;
}
void FadeOutPlatform::SetCollision(bool myBool)
{
	m_Collision = myBool;
}
bool FadeOutPlatform::GetIsInteractable()
{
	return m_isInteractable;
}
