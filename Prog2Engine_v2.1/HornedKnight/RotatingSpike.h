#pragma once
#include "Spike.h"

class RotatingSpike final:public Spike
{
public:
	RotatingSpike(const std::string& textPath, const Vector2f& pos,
		int rows = { 1 }, int columns = { 1 }, float frameDelay = { 0.f });

	void operator=(const RotatingSpike&) = delete;
	void operator=(const RotatingSpike&&) = delete;

	RotatingSpike(const RotatingSpike& obj) = delete;
	RotatingSpike(const RotatingSpike&& obj) = delete;

	~RotatingSpike();

	void Update(float elapsedSec);
	void Draw() const;
private:

	float m_Angle;

	//Sprite* m_Chain;
};

