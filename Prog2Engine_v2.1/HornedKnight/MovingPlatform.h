#pragma once
#include "Platform.h"
#include <iostream>

class MovingPlatform final:public Platform
{
public:
	MovingPlatform(const std::string& textPath, const Vector2f& startPos,float dist,float period);

	void Update(float elapsedSec) override;

private:
	//CONSTANTS
	const float TRAVEL_DIST;
	const float PERIOD;
	
	//Member varibles
	float m_XDeviation;
	float m_TickCounter;
	Vector2f m_StartPos;
};

