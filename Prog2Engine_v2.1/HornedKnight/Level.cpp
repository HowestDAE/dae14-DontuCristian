#include "pch.h"
#include "Level.h"

std::vector<std::vector<Point2f>> Level::m_ColliderArr = {};

std::vector<Platform*> Level::m_PlatformsArr = {};
std::vector<Enemy*> Level::m_EnemiesArr = {};
std::vector<DMGZone*> Level::m_DMGZoneArr = {};

Level::Level(const std::string& svgPath, const std::string& textureBackgroundPath, const std::string& textureForegroundPath):
	m_ScaleFactor{ 3.47f}
	//m_ScaleFactor{ 1.f }
{
	m_PlatformsArr.reserve(4);
	m_EnemiesArr.reserve(1);
	m_DMGZoneArr.reserve(27);
	m_BackgroundPath = textureBackgroundPath;
	m_ForegroundPath = textureForegroundPath;
	SVGParser::GetVerticesFromSvgFile(svgPath, m_ColliderArr);

	m_PlatformsArr.push_back(new MovingPlatform { "MovingPlatform.png",  Vector2f{982.f,30.f},70.f,5.f });
	m_PlatformsArr.push_back(new FadeOutPlatform{ "FadeOutPlatform.png", Vector2f{1845.f,20.f},3,5 });
	m_PlatformsArr.push_back(new FadeOutPlatform{ "FadeOutPlatform.png", Vector2f{1910.f,20.f},3,5 });
	m_PlatformsArr.push_back(new MovingPlatform { "MovingPlatform.png",  Vector2f{3195.f,30.f},180.f,13.f });

	m_EnemiesArr.push_back(new Enemy{ "Skelleton.png",Vector2f{164.f,43.f},15.f,20.f,35.f,3,5,0.1f });

	m_DMGZoneArr.push_back(new KillZone{ "Lava.png",Vector2f{1876.f,-2.f},1,2,0.3f});

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
	
	m_DMGZoneArr.push_back(new RotatingSpike{ "SpikeBall.png",Vector2f{2500.f,90.f},1,1,0.f });

	m_DMGZoneArr.push_back(new OrbitingSpike{ "SpikeBall.png",Rectf{2860.f,32.f,16.f,16.f},true, 1,1,0.f });
	m_DMGZoneArr.push_back(new OrbitingSpike{ "SpikeBall.png",Rectf{2908.f,32.f,16.f,16.f},false,1,1,0.f });
	m_DMGZoneArr.push_back(new OrbitingSpike{ "SpikeBall.png",Rectf{2956.f,32.f,16.f,16.f},true, 1,1,0.f });
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
	m_PlatformsArr.clear();
	m_EnemiesArr.clear();
	m_DMGZoneArr.clear();
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
	for (DMGZone* obj : m_DMGZoneArr)
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
	for (Enemy* obj : m_EnemiesArr)
	{
		obj->Draw();
	}
	for (DMGZone* obj : m_DMGZoneArr)
	{
		obj->Draw();
	}
	TextureManager::GetInstance()->GetTexture(m_ForegroundPath)->Draw();
}
float Level::GetScaleFactor() const
{
	return m_ScaleFactor;
}
