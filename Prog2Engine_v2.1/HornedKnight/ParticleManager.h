#pragma once
#include "Particle.h"
#include "Dust.h"
#include "Lava.h"
#include "Dash.h"
#include <iostream>

enum class ParticleType
{
	dust,
	lava,
	dash
};
class ParticleManager
{
public:
	//Gets the instance of my Particle Manager, 
	//so I have only one instance in the game
	static ParticleManager* GetInstance();

	//Rule of 5
	void operator=(const ParticleManager&) = delete;
	void operator=(const ParticleManager&&) = delete;

	ParticleManager (const ParticleManager& obj) = delete;
	ParticleManager(const ParticleManager&& obj) = delete;
	~ParticleManager();

	void Draw() const;
	void Update(float elapsedSec,float targetY);

	void CreateParticles(ParticleType pType, int pNr);

	void Emit(ParticleType pType,const Vector2f& pos);

private:

	ParticleManager();

	std::vector <Particle*> m_ParticleArr;
	static ParticleManager* m_Instance;
};

