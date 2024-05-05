#pragma once
#include "Particle.h"
class Dust:public Particle
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
	void Emit(const Vector2f& pos);
	void Destroy();

	void Draw() const;
private:

	float m_Opacity{1.f};
	float m_AccumulatedTime{};
	const float m_AliveTime{1.f};
	const float m_FadeOutTime{1.f};
	
};

