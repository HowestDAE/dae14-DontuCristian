#pragma once
#include "SVGParser.h"
#include "Sprite.h"
#include "utils.h"
#include "Camera.h"
#include "GameVars.h"

#include "DMGZone.h"
#include "KillZone.h"
#include "RotatingSpike.h"
#include "OrbitingSpike.h"
#include "Spike.h"
#include "Enemy.h"
#include "Platform.h"
#include "MovingPlatform.h"
#include "FadeOutPlatform.h"

class Level
{
public:
	Level(const std::string& svgPath, const std::string& textureBackgroundPath, const std::string& textureForegroundPath);

	//Rule of 3
	~Level();
	Level(const Level& obj) = delete;
	void operator=(const Level&) = delete;

	void Update(float elapsedSec);
	void Draw() const;

	float GetScaleFactor() const;

	//Map/Enemy colliders
	static std::vector<Platform*>			 m_PlatformsArr;
	static std::vector<std::vector<Point2f>> m_ColliderArr;
	static std::vector<Enemy*>				 m_EnemiesArr;
	static std::vector<DMGZone*>			 m_DMGZoneArr;


private:
	int m_PlatformsNr{2};
	float m_ScaleFactor;

	std::string m_BackgroundPath;
	std::string m_ForegroundPath;
};

