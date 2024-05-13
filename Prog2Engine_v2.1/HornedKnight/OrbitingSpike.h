#pragma once
#include "Spike.h"

class OrbitingSpike final:public Spike                       
{
public:
	OrbitingSpike(const std::string& textPath, const Rectf& targetRect, bool clockwise,
				  int rows = { 1 }, int columns = { 1 }, float frameDelay={0.f});

	void operator=(const OrbitingSpike&) = delete;
	void operator=(const OrbitingSpike&&) = delete;

	OrbitingSpike(const OrbitingSpike& obj) = delete;
	OrbitingSpike(const OrbitingSpike&& obj) = delete;

	~OrbitingSpike();

	void Update(float elapsedSec);
	void Draw() const;
private:
	//CONSTANTS
	const float SPEED{50.f};

	//Memmber variables
	bool	 m_Clockwise;

	Rectf	 m_TargetRect;
	Vector2f m_Velocity;
};

