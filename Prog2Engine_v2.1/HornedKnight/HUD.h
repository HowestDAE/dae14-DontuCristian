#pragma once
#include "Player.h"
#include "HealthSquare.h"
class HUD
{
public:
	HUD();
	~HUD();

	void Update(float elapsedSec);
	void Draw() const;

private:
	//CONSTANTS 
	const int HP_SQR_NR{6};
	const float MAX_BAR_WIDTH{18.f};

	Rectf m_BarOutline;
	Rectf m_BarShadow;
	Rectf m_BarFill;
	Rectf m_EmptyBar;

	//Member variables
	std::vector<HealthSquare*> m_HealthBarArr;

	//Methods
	void DrawRefillBar() const;
	void UpdateRefillBar();

	void DrawHealthBar() const;
	void UpdateHealthBar(float elapsedSec);
};

