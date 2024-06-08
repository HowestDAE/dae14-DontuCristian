#include "pch.h"
#include "HUD.h"

HUD::HUD()
{
	m_BarOutline = Rectf{ 10.f,87.f,20.f,3.5f };
	m_BarFill=Rectf{ 11.f,87.75f,18.f,2.f };

	m_BarShadow = Rectf{ 11.f,86.f,20.f,3.5f };
	m_EmptyBar = Rectf{ 11.f,87.75f,18.f,2.f };

	m_HealthBarArr.reserve(HP_SQR_NR);

	for (int idx{}; idx < HP_SQR_NR; idx++)
	{
		m_HealthBarArr.push_back(new HealthSquare{"HealthSquare.png",Vector2f{10.f + idx*6.f,94.f}});
	}
}HUD::~HUD()
{
	for (int idx{}; idx < m_HealthBarArr.size(); idx++)
	{
		delete m_HealthBarArr[idx];
		m_HealthBarArr[idx] = nullptr;
	}
}

void HUD::Update(float elapsedSec)
{
	UpdateHealthBar(elapsedSec);
	UpdateRefillBar();
}

void HUD::Draw() const
{
	DrawHealthBar();
	DrawRefillBar();
}

void HUD::DrawRefillBar() const
{
	utils::SetColor(Color4f{ 0.f,0.f,0.f,1.f });
	utils::FillRect(m_BarShadow);

	utils::SetColor(Color4f{ 1.f,1.f,1.f,1.f });
	utils::FillRect(m_BarOutline);

	utils::SetColor(Color4f{ 0.5f,0.5f,0.5f,1.5f });
	utils::FillRect(m_EmptyBar);

	utils::SetColor(Color4f{ 1.f,0.f,0.f,1.f });
	utils::FillRect(m_BarFill);
}

void HUD::UpdateRefillBar()
{
	m_BarFill.width = MAX_BAR_WIDTH * Player::GetBarPct();
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
	//Losing a heart
	for (int idx{ int(m_HealthBarArr.size()-1) }; idx >= Player::GetNrLives(); idx--)
	{
		m_HealthBarArr.at(idx)->SetIsFilled(false);
	}

	//Getting a heart back
	for (int idx{};idx < Player::GetNrLives() ;idx++)
	{
		m_HealthBarArr.at(idx)->SetIsFilled(true);
	}
}
  
