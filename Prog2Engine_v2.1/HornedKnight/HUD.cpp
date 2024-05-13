#include "pch.h"
#include "HUD.h"

HUD::HUD()
{
	m_HealthBarArr.reserve(HP_SQR_NR);

	for (int idx{}; idx < HP_SQR_NR; idx++)
	{
		m_HealthBarArr.push_back(new HealthSquare{"HealthSquare.png",Vector2f{10.f + idx*6.f,102.f}});
	}
}HUD::~HUD()
{
	m_HealthBarArr.clear();
}

void HUD::Update(float elapsedSec)
{
	UpdateHealthBar(elapsedSec);
}

void HUD::Draw() const
{
	DrawHealthBar();
}

void HUD::DrawHealthBar() const
{
	for (HealthSquare* healthSqr : m_HealthBarArr)
	{
		healthSqr->Draw();
	}
}

void HUD::UpdateHealthBar(float elapsedSec)
{
	for (int idx{};idx<m_HealthBarArr.size();idx++)
	{
		m_HealthBarArr[idx]->Update(elapsedSec);
	}
	for (int idx{ int(m_HealthBarArr.size()-1) }; idx >= Player::GetNrLives(); idx--)
	{
		m_HealthBarArr.at(idx)->SetIsFilled(false);
	}
}
  
