#include "pch.h"
#include "BulletEmitter.h"

std::vector <Bullet*> BulletEmitter::m_BulletArr = {};

BulletEmitter::BulletEmitter(const Vector2f& pos, const Vector2f& direction, float destructDist,  float firstBulletDelay):
	m_Pos{pos},
	m_Dir{direction},
	m_AccumulatedTime{EMISSION_DELAY - firstBulletDelay},
	DESTRUCT_DIST{destructDist}
{
}

BulletEmitter::~BulletEmitter()
{
	for (Bullet* bullet : m_BulletArr)
	{
		delete bullet;
		bullet = nullptr;
	}
	m_BulletArr.clear();
}

void BulletEmitter::Draw() const
{
	for (Bullet* bullet : m_BulletArr)
	{
		bullet->Draw();
	}
}

void BulletEmitter::Update(float elapsedSec)
{
	DestroyBullet();
	for (Bullet* bullet : m_BulletArr)
	{
		bullet->Update(elapsedSec);
	}
}

void BulletEmitter::Emit(float elapsedSec,const std::string& textPath)
{
	m_AccumulatedTime += elapsedSec;
	if (m_AccumulatedTime >= EMISSION_DELAY)
	{
		m_BulletArr.push_back(new Bullet{ textPath,m_Pos,m_Dir,DESTRUCT_DIST,1,1,0.f });
		m_AccumulatedTime -= EMISSION_DELAY;
	}
}

void BulletEmitter::Shoot(const std::string& textPath)
{
	m_BulletArr.push_back(new Bullet{ textPath,m_Pos,Vector2f{-1.f,0.f},DESTRUCT_DIST,1,4,0.2f });
}

void BulletEmitter::DestroyBullet()
{
	for (int idx{};idx<m_BulletArr.size();idx++)
	{
		if (m_BulletArr[idx]->GetIsDestroyed() == true)
		{
			delete m_BulletArr[idx];
			m_BulletArr[idx] = nullptr;

			m_BulletArr.erase(m_BulletArr.begin() + idx);
		}
	}
	m_BulletArr.shrink_to_fit();
}