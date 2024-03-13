#include "pch.h"
#include "SpriteManager.h"

int SpriteManager::m_SpriteCount = 0;

std::vector <Sprite*> SpriteManager::m_SpriteArrayPtr = {0};

SpriteManager::SpriteManager() 
{
}

SpriteManager::~SpriteManager()
{
	for (int idx{}; idx < m_SpriteCount; idx++)
	{
		delete m_SpriteArrayPtr[idx];
	}
}
void SpriteManager::CreateSprite(Sprite* sprite)
{
	m_SpriteArrayPtr.push_back(sprite);
	m_SpriteCount++;
}
