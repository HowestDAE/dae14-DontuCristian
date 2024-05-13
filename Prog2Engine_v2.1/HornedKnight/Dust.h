#pragma once
#include "Particle.h"
class Dust final:public Particle
{
public:
	Dust(const Vector2f& pos);

	//Rule of 5
	~Dust();
	void operator= (const Dust&) = delete;
	void operator= (const Dust&&) = delete;

	Dust(const Dust&& obj) = delete;
	Dust(const Dust& obj) = delete;

	void Update(float elapsedSec);

	void Draw() const;

	static int m_DustPartCount;

private:
	//CONSTANTS
	const float ALIVE_TIME{ 0.5f };
	const float FADEOUT_TIME{ 0.5f };

	//Member variables
	float m_Opacity{1.f};
	float m_AccumulatedTime{};	
};

