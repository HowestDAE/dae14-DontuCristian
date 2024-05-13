#pragma once
#include "Particle.h"
class Dash final:public Particle
{
public:
	Dash(const Vector2f& pos);

	//Rule of 5
	void operator= (const Dash&) = delete;
	void operator= (const Dash&&) = delete;
	Dash(const Dash& obj) = delete;
	Dash(const Dash&& obj) = delete;

	~Dash();

	void Update(float elapsedSec);
	void Draw() const;

	static int m_DashPartCount;

private:
	//CONSTANTS
	const float ALIVE_TIME   { 0.5f };
	const float FADEOUT_TIME { 0.5f };

	//Member variables
	float m_Opacity{ 1.f };
	float m_AccumulatedTime{};
};

