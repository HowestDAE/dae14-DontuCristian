#pragma once
#include "Particle.h"
class Blood final:public Particle
{
public:
	Blood(const Vector2f& pos);

	//Rule of 5
	void operator= (const Blood&) = delete;
	void operator= (const Blood&&) = delete;
	Blood(const Blood& obj) = delete;
	Blood(const Blood&& obj) = delete;

	~Blood();

	void Update(float elapsedSec) override;
	void Draw() const override;

	static int m_BloodPartCount;

private:
	//CONSTANTS
	const float ALIVE_TIME{ 1.f };
	const float FADEOUT_TIME{ 1.f };

	//Member variables
	float m_Opacity{ 1.f };
	float m_AccumulatedTime{};
};

