#pragma once
#include "Particle.h"
class Lava final:public Particle
{
public:
	Lava(const Vector2f& pos);

	//Rule of 5
	void operator= (const Lava&) = delete;
	void operator= (const Lava&&) = delete;
	Lava(const Lava& obj) = delete;
	Lava(const Lava&& obj) = delete;

	~Lava();

	void Update(float elapsedSec,float targetY);
	void Draw() const;

	static int m_LavaPartCount;

private:
	//CONSTANTS
	const static float MAX_SIZE;
	const static float MAX_DIST; //max dist from the emition point

	//Member variables
	float m_Size;
	float m_DestroyRayY;//the y level at which the particles get destroyed
};

