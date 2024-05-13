#include "pch.h"
#include "Level.h"

std::vector<std::vector<Point2f>> Level::m_ColliderArr = {};

std::vector<Platform*> Level::m_PlatformsArr = {};
std::vector<Enemy*> Level::m_EnemiesArr = {};
std::vector<DMGZone*> Level::m_DMGZoneArr = {};

Level::Level(const std::string& svgPath, const std::string& texturePath):
	m_ScaleFactor{ 3.47f}
{
	m_Path = texturePath;
	SVGParser::GetVerticesFromSvgFile(svgPath,m_ColliderArr);

	m_PlatformsArr.push_back(new MovingPlatform { "MovingPlatform.png",  Vector2f{982.f,30.f},70.f,5.f });
	m_PlatformsArr.push_back(new FadeOutPlatform{ "FadeOutPlatform.png", Vector2f{1845.f,20.f},3,5 });
	m_PlatformsArr.push_back(new FadeOutPlatform{ "FadeOutPlatform.png", Vector2f{1910.f,20.f},3,5 });
	m_PlatformsArr.push_back(new MovingPlatform { "MovingPlatform.png",  Vector2f{3195.f,30.f},180.f,13.f });

	m_EnemiesArr.push_back(new Enemy{ "Skelleton.png",Vector2f{164.f,43.f},15.f,20.f,35.f,3,5,0.1f });

	m_DMGZoneArr.push_back(new Spike{ "Spike.png",Vector2f{253.f,20.f},2,5,0.1f });
	m_DMGZoneArr.push_back(new Spike{ "Spike.png",Vector2f{643.f,20.f},2,5,0.1f });
	m_DMGZoneArr.push_back(new Spike{ "Spike.png",Vector2f{717.f,20.f},2,5,0.1f });
	m_DMGZoneArr.push_back(new Spike{ "Spike.png",Vector2f{3043.f,36.f},2,5,0.1f });

	m_DMGZoneArr.push_back(new DMGZone{ "SpikeBaseTexture.png",Vector2f{1813.f,4.f},1,1,0.f });
	m_DMGZoneArr.push_back(new DMGZone{ "SpikeBaseTexture.png",Vector2f{1829.f,4.f},1,1,0.f });
	m_DMGZoneArr.push_back(new DMGZone{ "SpikeBaseTexture.png",Vector2f{1845.f,4.f},1,1,0.f });
	m_DMGZoneArr.push_back(new DMGZone{ "SpikeBaseTexture.png",Vector2f{1861.f,4.f},1,1,0.f });
	m_DMGZoneArr.push_back(new DMGZone{ "SpikeBaseTexture.png",Vector2f{1877.f,4.f},1,1,0.f });
	m_DMGZoneArr.push_back(new DMGZone{ "SpikeBaseTexture.png",Vector2f{1893.f,4.f},1,1,0.f });
	m_DMGZoneArr.push_back(new DMGZone{ "SpikeBaseTexture.png",Vector2f{1909.f,4.f},1,1,0.f });
	m_DMGZoneArr.push_back(new DMGZone{ "SpikeBaseTexture.png",Vector2f{1925.f,4.f},1,1,0.f });
	m_DMGZoneArr.push_back(new DMGZone{ "SpikeBaseTexture.png",Vector2f{1941.f,4.f},1,1,0.f });

	m_DMGZoneArr.push_back(new DMGZone{ "SpikeBaseTexture.png",Vector2f{2180.f,20.f},1,1,0.f });
	m_DMGZoneArr.push_back(new DMGZone{ "SpikeBaseTexture.png",Vector2f{2196.f,20.f},1,1,0.f });
	m_DMGZoneArr.push_back(new DMGZone{ "SpikeBaseTexture.png",Vector2f{2212.f,20.f},1,1,0.f });
	m_DMGZoneArr.push_back(new DMGZone{ "SpikeBaseTexture.png",Vector2f{2228.f,20.f},1,1,0.f });

	m_DMGZoneArr.push_back(new DMGZone{ "SpikeBaseDown.png",Vector2f{2228.f,76.f},1,1,0.f });
	m_DMGZoneArr.push_back(new DMGZone{ "SpikeBaseDown.png",Vector2f{2244.f,76.f},1,1,0.f });
	m_DMGZoneArr.push_back(new DMGZone{ "SpikeBaseDown.png",Vector2f{2260.f,76.f},1,1,0.f });

	m_DMGZoneArr.push_back(new DMGZone{ "SpikeBaseDown.png",Vector2f{2740.f,76.f},1,1,0.f });
	m_DMGZoneArr.push_back(new DMGZone{ "SpikeBaseDown.png",Vector2f{2756.f,76.f},1,1,0.f });
	m_DMGZoneArr.push_back(new DMGZone{ "SpikeBaseDown.png",Vector2f{2772.f,76.f},1,1,0.f });
	m_DMGZoneArr.push_back(new DMGZone{ "SpikeBaseDown.png",Vector2f{2788.f,76.f},1,1,0.f });


	m_DMGZoneArr.push_back(new OrbitingSpike{ "SpikeBall.png",Rectf{2860.f,32.f,16.f,16.f},true, 1,1,0.f });
	m_DMGZoneArr.push_back(new OrbitingSpike{ "SpikeBall.png",Rectf{2908.f,32.f,16.f,16.f},false,1,1,0.f });
	m_DMGZoneArr.push_back(new OrbitingSpike{ "SpikeBall.png",Rectf{2956.f,32.f,16.f,16.f},true, 1,1,0.f });
}

Level::~Level()
{
	for (Platform* obj : m_PlatformsArr)
	{
		delete obj;
	}
	for (Enemy* obj : m_EnemiesArr)
	{
		delete obj;
	}
	for (DMGZone* obj : m_DMGZoneArr)
	{
		delete obj;
	}
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
	TextureManager::GetInstance()->GetTexture(m_Path)->Draw();

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

	utils::SetColor(Color4f{ 0.f, 0.f, 1.f, 1.f });
	utils::DrawRect(rect);
}
float Level::GetScaleFactor() const
{
	return m_ScaleFactor;
}