#pragma once
#include <iostream>
#include "Sprite.h"
#include "utils.h"

class Particle
{
public:

	Particle(const Vector2f& pos,const Vector2f& vel);
	
	//Rule of 5
	virtual ~Particle();
	void operator=(const Particle&) = delete;
	void operator=(const Particle&&) = delete;
	Particle(const Particle& obj) = delete;
	Particle(const Particle&& obj) = delete;


	virtual void Update(float elapsedSec);
	virtual void Update(float elapsedSec,float targetY);
	virtual void Emit(const Vector2f& pos);
	virtual void Destroy();

	virtual void Draw() const;

	bool GetIsDestroyed();

	static int m_ParticleCount;

protected:
	bool m_isDestroyed = {true};

	Vector2f m_Position;
	Vector2f m_Velocity;
};

