#pragma once
#include "Player.h"
#include "HealthSquare.h"
#include "StringSprite.h"

class HUD
{
public:
	HUD();
	~HUD();

	void Update(float elapsedSec);
	void Draw() const;

private:
	//static members
	bool m_canDraw{};

	//CONSTANTS 
	const int HP_SQR_NR{6};
	const float MAX_BAR_WIDTH{18.f};
	const float ALIVE_TEXT_TIME{ 1.f };

	float m_AccumulatedTime{};


	//Member variables
	std::vector<HealthSquare*> m_HealthBarArr;
	StringSprite* m_HudText;

	Rectf m_BarOutline;
	Rectf m_BarShadow;
	Rectf m_BarFill;
	Rectf m_EmptyBar;

	//Methods
	void DrawRefillBar() const;
	void UpdateRefillBar();

	void DrawHealthBar() const;
	void UpdateHealthBar(float elapsedSec);
};

