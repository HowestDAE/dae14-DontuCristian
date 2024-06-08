#pragma once
#include "DMGZone.h"
#include "utils.h"
#include "ParticleManager.h"

class Fireball final: public DMGZone
{

public:
	Fireball(const std::string& textPath, const Vector2f& startPos, int rows = { 1 }, int columns = { 1 }, float frameDelay = { 0.f });

	//Rule of 5
	void operator=(const Fireball&) = delete;
	void operator=(const Fireball&&) = delete;

	Fireball(const Fireball& obj) = delete;
	Fireball(const Fireball&& obj) = delete;
	 ~Fireball();

	void Update(float elapsedSec);

	float GetYVelocity();

private:
	//CONSTANTS
	const float TRAVEL_DIST;
	const float PERIOD;

	//Member varibles
	float m_VelocityY;
	float m_YDeviation;
	float m_TickCounter;
	Vector2f m_StartPos;


};
