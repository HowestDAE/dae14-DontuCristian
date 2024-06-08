#pragma once
#include "Particle.h"
#include "Dust.h"
#include "Dash.h"
#include "Blood.h"
#include <iostream>

enum class ParticleType
{
	dust,
	dash,
	blood
};
class ParticleManager
{
public:

	static ParticleManager* GetInstance();

	static void DeleteSingleton();
	//Rule of 5
	void operator=(const ParticleManager&) = delete;
	void operator=(const ParticleManager&&) = delete;

	ParticleManager (const ParticleManager& obj) = delete;
	ParticleManager(const ParticleManager&& obj) = delete;
	~ParticleManager();

	void Draw() const;
	void Update(float elapsedSec);

	void Emit(float elapsedSec,const ParticleType& pType,const Vector2f& pos);

	void Destroy();

private:

	ParticleManager() = default;
	const float DESTRUCT_TIME {2.f};

	float m_AccumulatedTime{};

	std::vector <Particle*> m_ParticleArr;

	static ParticleManager* m_Instance;
};

