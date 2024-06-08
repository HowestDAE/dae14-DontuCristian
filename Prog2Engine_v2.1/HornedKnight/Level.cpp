#include "pch.h"
#include "Level.h"

std::vector<std::vector<Point2f>> Level::m_ColliderArr = {};

std::vector<Platform*> Level::m_PlatformsArr = {};
std::vector<Enemy*> Level::m_EnemiesArr = {};
std::vector<DMGZone*> Level::m_DMGZoneArr = {};
std::vector<CheckPoint*> Level::m_CheckPoints = {};

Level::Level(const std::string& svgPath, const std::string& textureBackgroundPath, const std::string& textureForegroundPath)
{
	m_PlatformsArr.reserve(PLATFORM_NR);
	m_EnemiesArr.reserve(ENEMY_NR);
	m_DMGZoneArr.reserve(DMG_ZONE_NR);
	m_CheckPoints.reserve(CHEKPOINT_NR);

	m_BackgroundPath = textureBackgroundPath;
	m_ForegroundPath = textureForegroundPath;
	SVGParser::GetVerticesFromSvgFile(svgPath, m_ColliderArr);

	m_PlatformsArr.push_back(new MovingPlatform{ "MovingPlatform.png",  Vector2f{3195.f,30.f},180.f,13.f });
	m_PlatformsArr.push_back(new MovingPlatform{ "MovingPlatform.png",  Vector2f{982.f,30.f},70.f,5.f });
	m_PlatformsArr.push_back(new FadeOutPlatform{ "FadeOutPlatform.png", Vector2f{1845.f,20.f},3,5 });
	m_PlatformsArr.push_back(new FadeOutPlatform{ "FadeOutPlatform.png", Vector2f{1910.f,20.f},3,5 });

	m_EnemiesArr.push_back(new Enemy{ "Skelleton.png", Vector2f{164.f,40.f},Vector2f{196.f,40.f},EnemyType::normal,15.f,20.f,4,5,0.1f });
	m_EnemiesArr.push_back(new Enemy{ "Cobra.png",	   Vector2f{308.f,40.f},Vector2f{340.f,40.f},EnemyType::normal,15.f,16.f,4,6,0.1f });
	m_EnemiesArr.push_back(new Enemy{ "WeirdSlime.png",Vector2f{356.f,21.f},Vector2f{406.f,21.f},EnemyType::normal,18.f,12.f,3,6,0.1f });
	m_EnemiesArr.push_back(new Enemy{ "WeirdSlime.png",Vector2f{470.f,21.f},Vector2f{534.f,21.f},EnemyType::normal,18.f,12.f,3,6,0.1f });
	m_EnemiesArr.push_back(new Enemy{ "Cobra.png",	   Vector2f{548.f,40.f},Vector2f{595.f,40.f},EnemyType::normal,15.f,16.f,4,6,0.1f });

	m_EnemiesArr.push_back(new Enemy{ "Skelleton.png", Vector2f{890.f,40.f},Vector2f{890.f,40.f},EnemyType::ranged,15.f,20.f,4,5,0.1f });
	m_EnemiesArr.push_back(new Enemy{ "Cobra.png",	   Vector2f{1220.f,40.f},Vector2f{1220.f,40.f},EnemyType::ranged,15.f,16.f,4,6,0.1f });

	m_EnemiesArr.push_back(new Enemy{ "Bat.png",	   Vector2f{1298.f,138.f},Vector2f{1362.f,115.f},EnemyType::bat,15.f,10.f,3,5,0.1f });
	m_EnemiesArr.push_back(new Enemy{ "Bat.png",	   Vector2f{1362.f,138.f},Vector2f{1298.f,115.f},EnemyType::bat,15.f,10.f,3,5,0.1f });

	m_EnemiesArr.push_back(new Enemy{ "Skelleton.png", Vector2f{1554.f,55.f},Vector2f{1557.f,60.f},EnemyType::ranged,15.f,20.f,4,5,0.1f });
	m_EnemiesArr.push_back(new Enemy{ "Skelleton.png", Vector2f{1554.f,23.f},Vector2f{1557.f,23.f},EnemyType::ranged,15.f,20.f,4,5,0.1f });

	m_EnemiesArr.push_back(new Enemy{ "SpikeAnimal.png", Vector2f{1637.f,23.f},Vector2f{1700.f,23.f},EnemyType::normal,15.f,16.f,3,7,0.1f });
	m_EnemiesArr.push_back(new Enemy{ "SpikeAnimal.png", Vector2f{1729.f,23.f},Vector2f{1795.f,23.f},EnemyType::normal,15.f,16.f,3,7,0.1f });

	m_EnemiesArr.push_back(new Enemy{ "WeirdSlime.png", Vector2f{1959.f,23.f},Vector2f{2000.f,22.f},EnemyType::normal,18.f,12.f,3,6,0.1f });

	m_EnemiesArr.push_back(new Enemy{ "Cobra.png",	   Vector2f{2777.f,40.f},Vector2f{2777.f,40.f},EnemyType::ranged,15.f,16.f,4,6,0.1f });

	m_EnemiesArr.push_back(new Enemy{ "SpikeAnimal.png", Vector2f{3089.f,23.f},Vector2f{3143.f,40.f},EnemyType::normal,15.f,16.f,3,7,0.1f });


	m_CheckPoints.push_back(new CheckPoint{ "CheckPoint.png", Vector2f{40.f,23.f} });
	m_CheckPoints.push_back(new CheckPoint{ "CheckPoint.png", Vector2f{1270.f,23.f} });
	m_CheckPoints.push_back(new CheckPoint{ "CheckPoint.png", Vector2f{2155.f,151.f} });
	m_CheckPoints.push_back(new CheckPoint{ "CheckPoint.png", Vector2f{2629.f,39.f} });


	m_DMGZoneArr.push_back(new Fireball{ "Lavaball.png" , Vector2f{805.f,0.f} });
	m_DMGZoneArr.push_back(new Fireball{ "Lavaball.png" , Vector2f{2398.f,5.f} });
	m_DMGZoneArr.push_back(new Fireball{ "Lavaball.png" , Vector2f{2475.f,5.f} });
	m_DMGZoneArr.push_back(new Fireball{ "Lavaball.png" , Vector2f{2555.f,5.f} });

	m_DMGZoneArr.push_back(new KillZone{ "Lava.png",Vector2f{0.f,-2.f},1,2,0.3f});
	m_DMGZoneArr.push_back(new KillZone{ "Lava.png",Vector2f{3700.f,-2.f},1,2,0.3f });


	for (int idx{}; idx < 3; idx++)
	{
		m_DMGZoneArr.push_back(new KillZone{ "SpikeBaseLeft.png",Vector2f{3272.f,56.f - idx*16.f},1,1,0.3f });
		m_DMGZoneArr.push_back(new KillZone{ "SpikeBaseRight.png",Vector2f{3296.f,56.f - idx * 16.f},1,1,0.3f });

		m_DMGZoneArr.push_back(new KillZone{ "SpikeBaseLeft.png",Vector2f{3448.f,56.f - idx * 16.f},1,1,0.3f });
		m_DMGZoneArr.push_back(new KillZone{ "SpikeBaseRight.png",Vector2f{3472.f,56.f - idx * 16.f},1,1,0.3f });
	}
	m_DMGZoneArr.push_back(new Spike{ "Spike.png",Vector2f{3284.f,68.f},2,5,0.1f });

	m_DMGZoneArr.push_back(new Spike{ "Spike.png",Vector2f{3364.f,20.f},2,5,0.1f });
	m_DMGZoneArr.push_back(new Spike{ "Spike.png",Vector2f{3380.f,20.f},2,5,0.1f });

	m_DMGZoneArr.push_back(new Spike{ "Spike.png",Vector2f{3460.f,68.f},2,5,0.1f });

	m_DMGZoneArr.push_back(new Spike{ "Spike.png",Vector2f{253.f,20.f},2,5,0.1f });
	m_DMGZoneArr.push_back(new Spike{ "Spike.png",Vector2f{643.f,20.f},2,5,0.1f });
	m_DMGZoneArr.push_back(new Spike{ "Spike.png",Vector2f{717.f,20.f},2,5,0.1f });
	m_DMGZoneArr.push_back(new Spike{ "Spike.png",Vector2f{3043.f,36.f},2,5,0.1f });
	
	for (int idx{}; idx < 9; idx++)
	{
		m_DMGZoneArr.push_back(new DMGZone{ "SpikeBaseTexture.png",Vector2f{1813.f + idx * 16.f,4.f},1,1,0.f });
	}	
	for (int idx{}; idx < 4; idx++)
	{
		m_DMGZoneArr.push_back(new DMGZone{ "SpikeBaseTexture.png",Vector2f{2180.f + idx * 16.f,20.f},1,1,0.f });
	}
	for (int idx{}; idx < 3; idx++)
	{
		m_DMGZoneArr.push_back(new DMGZone{ "SpikeBaseDown.png",Vector2f{2228.f + idx * 16.f,76.f},1,1,0.f });
	}
	
	for (int idx{}; idx < 4; idx++)
	{
		m_DMGZoneArr.push_back(new DMGZone{ "SpikeBaseDown.png",Vector2f{2740.f + idx * 16.f,76.f},1,1,0.f });
	}
	

	m_DMGZoneArr.push_back(new OrbitingSpike{ "SpikeBall.png",Rectf{2860.f,32.f,16.f,16.f},true, 1,1,0.f });
	m_DMGZoneArr.push_back(new OrbitingSpike{ "SpikeBall.png",Rectf{2908.f,32.f,16.f,16.f},false,1,1,0.f });
	m_DMGZoneArr.push_back(new OrbitingSpike{ "SpikeBall.png",Rectf{2956.f,32.f,16.f,16.f},true, 1,1,0.f });

	m_EmitterArr.push_back(new BulletEmitter{ Vector2f{2069.f,160.f},Vector2f{0.f,-1.f}, 1.f});
	m_EmitterArr.push_back(new BulletEmitter{ Vector2f{2099.f,160.f},Vector2f{0.f,-1.f}, 2.f});
	m_EmitterArr.push_back(new BulletEmitter{ Vector2f{2665.f,25.f}, Vector2f{1.f,0.f},  0.f });
}

Level::~Level()
{
	for (Platform* obj : m_PlatformsArr)
	{
		delete obj;
		obj = nullptr;
	}
	for (Enemy* obj : m_EnemiesArr)
	{
		delete obj;
		obj = nullptr;
	}
	for (DMGZone* obj : m_DMGZoneArr)
	{
		delete obj;
		obj = nullptr;
	}
	for (CheckPoint* obj : m_CheckPoints)
	{
		delete obj;
		obj = nullptr;
	}
	for (BulletEmitter* obj : m_EmitterArr)
	{
		delete obj;
		obj = nullptr;
	}
	m_PlatformsArr.clear();
	m_EnemiesArr.clear();
	m_DMGZoneArr.clear();
	m_CheckPoints.clear();
	m_EmitterArr.clear();
}
void Level::Update(float elapsedSec)
{
	for (Platform* obj : m_PlatformsArr)
	{
		obj->Update(elapsedSec);
	}
	for (Enemy* obj : m_EnemiesArr)
	{
		obj->Update(elapsedSec);
	}
	m_EmitterArr[0]->Emit(elapsedSec,"SpikeBulletDown.png");
	m_EmitterArr[1]->Emit(elapsedSec, "SpikeBulletDown.png");
	m_EmitterArr[2]->Emit(elapsedSec, "SpikeBulletRight.png");
	for (BulletEmitter* obj : m_EmitterArr)
	{
		obj->Update(elapsedSec);
	}
	for (DMGZone* obj : m_DMGZoneArr)
	{
		obj->Update(elapsedSec);
	}
	for (CheckPoint* obj : m_CheckPoints)
	{
		obj->Update(elapsedSec);
	}
}
void Level::Draw() const
{
	TextureManager::GetInstance()->GetTexture(m_BackgroundPath)->Draw();
	
	utils::SetColor(Color4f{ 0,1,0,1 });
	
	for (std::vector<Point2f> obj : m_ColliderArr)
	{
		utils::DrawPolygon(obj, true);
	}
	for (Platform* obj : m_PlatformsArr)
	{
		obj->Draw();
	}
	for (BulletEmitter* obj : m_EmitterArr)
	{
		obj->Draw();
	}
	for (Enemy* obj : m_EnemiesArr)
	{
		obj->Draw();
	}
	for (DMGZone* obj : m_DMGZoneArr)
	{
		obj->Draw();
	}
	for (CheckPoint* obj : m_CheckPoints)
	{
		obj->Draw();
	}
	utils::DrawRect(m_ExitDoor);
	TextureManager::GetInstance()->GetTexture(m_ForegroundPath)->Draw();
}
float Level::GetScaleFactor() const
{
	return SCALE_FACTOR;
}

Rectf Level::GetExitDoor() const
{
	return m_ExitDoor;
}
