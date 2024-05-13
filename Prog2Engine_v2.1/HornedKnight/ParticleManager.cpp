#include "pch.h"
#include "ParticleManager.h"

ParticleManager* ParticleManager::m_Instance = {};

ParticleManager* ParticleManager::GetInstance()
{
	m_Instance = (m_Instance != nullptr) ? m_Instance : new ParticleManager;
	return m_Instance;
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
		if (obj != nullptr)
		{
			obj->Draw();
		}
	}
}

void ParticleManager::Update(float elapsedSec,float targetY)
{
	Destroy();
	for (Particle* obj : m_ParticleArr)
	{
		if (obj != nullptr)
		{
			obj->Update(elapsedSec);
		}
		Lava* lavaParticles = dynamic_cast<Lava*>(obj);

		if (lavaParticles)
		{
			obj->Update(elapsedSec,targetY);
		}
	}
}

void ParticleManager::Emit(float elapsedSec, const ParticleType& pType, const Vector2f& pos)
{
	switch (pType)
	{
	case ParticleType::dust:		
		for (int idx{}; idx < 5; idx++)
		{
			m_ParticleArr.push_back(new Dust{ pos });
		}
		break;
	case ParticleType::lava:
		for (int idx{}; idx < 30; idx++)
		{
			if(Lava::m_LavaPartCount < 30)
			m_ParticleArr.push_back(new Lava{ Vector2f{pos.x + float(rand()%10-5),pos.y-float(rand()%25)}});
		}
		break;
	case ParticleType::blood:
		for (int idx{}; idx < 10; idx++)
		{
				m_ParticleArr.push_back(new Blood{ pos });
		}
		break;
	case ParticleType::dash:
		const int pPerSec{ 60 };//particles per sec
		const float interval{ 1.f / pPerSec };//interval between particles emission

		m_AccumulatedTime += elapsedSec;
		if (m_AccumulatedTime >= interval)
		{
			m_ParticleArr.push_back(new Dash{ pos });
			m_AccumulatedTime -= interval;
		}
		break;
	}
}

void ParticleManager::Destroy()
{
	for (int idx{};idx<m_ParticleArr.size();idx++)
	{
		if (m_ParticleArr[idx]->GetIsDestroyed())
		{
			delete m_ParticleArr[idx];
			m_ParticleArr[idx] = nullptr;
			
			m_ParticleArr.erase(m_ParticleArr.begin() + idx);
		}
	}
}

