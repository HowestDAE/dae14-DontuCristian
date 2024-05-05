#include "pch.h"
#include "ParticleManager.h"

ParticleManager* ParticleManager::m_Instance = {};

ParticleManager* ParticleManager::GetInstance()
{
	m_Instance = (m_Instance != nullptr) ? m_Instance : new ParticleManager;
	return m_Instance;
}
ParticleManager::ParticleManager()
{
}
ParticleManager::~ParticleManager()
{
	for (Particle* obj : m_ParticleArr)
	{
		delete obj;
	}
}

void ParticleManager::Draw() const
{
	for (Particle* obj:m_ParticleArr)
	{
		obj->Draw();
	}
}

void ParticleManager::Update(float elapsedSec,float targetY)
{
	for (Particle* obj : m_ParticleArr)
	{
		obj->Update(elapsedSec);
		
		Lava* lavaParticles = dynamic_cast<Lava*>(obj);

		if (lavaParticles)
		{
			obj->Update(elapsedSec,targetY);
		}
	}
}

void ParticleManager::CreateParticles(ParticleType pType, int pNr)
{
	switch (pType)
	{
	case ParticleType::dust:
		m_ParticleArr.reserve(pNr);
		for (int idx{}; idx < pNr; idx++)
			m_ParticleArr.push_back(new Dust{ Vector2f{-100.f,-100.f}});
		break;
	case ParticleType::lava:
		m_ParticleArr.reserve(pNr);
		for (int idx{}; idx < pNr; idx++)
			m_ParticleArr.push_back(new Lava{ Vector2f{-100.f,-100.f} });
		break;
	case ParticleType::dash:
		m_ParticleArr.reserve(pNr);
		for (int idx{}; idx < pNr; idx++)
			m_ParticleArr.push_back(new Dash{ Vector2f{-100.f,-100.f}});
		break;

	}
}
void ParticleManager::Emit(ParticleType pType,const Vector2f& pos)
{
	int current_DP_Count{};
	for (Particle* obj:m_ParticleArr)
	{
		if (pType == ParticleType::dust)
		{
			Dust* dustParticles = dynamic_cast<Dust*>(obj);
			
			if (dustParticles) 
			{
				current_DP_Count++;
				obj->Emit(pos);
			}
		}
		if (pType == ParticleType::lava)
		{
			Lava* lavaParticles = dynamic_cast<Lava*>(obj);
			if (lavaParticles)
			{
				lavaParticles->Emit(pos);
			}
		}
		if (pType == ParticleType::dash)
		{
			Dash* dashParticles = dynamic_cast<Dash*>(obj);
			if (dashParticles)
			{
				dashParticles->Emit(pos);
			}
		}
	}
}
