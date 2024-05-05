#pragma once
#include "Particle.h"
class Dash :public Particle
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

	void Emit(Vector2f pos);

private:

	float m_Opacity{ 1.f };
	float m_ElapsedSec{};
	float m_AccumulatedTime{};

	//Constants
	const float m_AliveTime{1.f};
	const float m_FadeOutTime{1.f};
};

