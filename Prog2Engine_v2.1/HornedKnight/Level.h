#pragma once
#include "SVGParser.h"
#include "Sprite.h"
#include "utils.h"
#include "Camera.h"
#include "GameVars.h"

#include "BulletEmitter.h"
#include "FireBall.h"
#include "DMGZone.h"
#include "KillZone.h"
#include "OrbitingSpike.h"
#include "Spike.h"
#include "Enemy.h"
#include "Platform.h"
#include "MovingPlatform.h"
#include "FadeOutPlatform.h"
#include "CheckPoint.h"

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
	Rectf GetExitDoor() const;

	//Map/Enemy colliders
	static std::vector<Platform*>			 m_PlatformsArr;
	static std::vector<std::vector<Point2f>> m_ColliderArr;
	static std::vector<Enemy*>				 m_EnemiesArr;
	static std::vector<DMGZone*>			 m_DMGZoneArr;
	static std::vector<CheckPoint*>			 m_CheckPoints;


private:
	//CONSTANTS
	const int PLATFORM_NR	{ 4 };
	const int DMG_ZONE_NR	{ 46 };
	const int ENEMY_NR		{ 16 };
	const int CHEKPOINT_NR	{ 4 };
	const float SCALE_FACTOR{ 3.13f };

	//Members
	int m_PlatformsNr{2};

	Rectf	m_ExitDoor{3645.f,15.f,45.f,40.f};

	std::vector<BulletEmitter*> m_EmitterArr {};

	std::string m_BackgroundPath;
	std::string m_ForegroundPath;
};

