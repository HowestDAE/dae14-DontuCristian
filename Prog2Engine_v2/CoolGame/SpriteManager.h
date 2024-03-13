#pragma once
#include <iostream>
#include <vector>
#include "Sprite.h"

class SpriteManager
{
public:
	
	SpriteManager();
	~SpriteManager();

	static void CreateSprite(Sprite* sprite);

	static int m_SpriteCount;

private:
	static SpriteManager* m_SpriteManager;

	static std::vector <Sprite*> m_SpriteArrayPtr;
};
