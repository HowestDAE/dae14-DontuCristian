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

	//Member variables
	std::vector<HealthSquare*> m_HealthBarArr;

	//Methods
	void DrawHealthBar() const;
	void UpdateHealthBar(float elapsedSec);
};

