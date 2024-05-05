#include "pch.h"
#include "Level.h"

std::vector<std::vector<Point2f>> Level::m_ColliderArr = {};

std::vector<Platform*> Level::m_PlatformsArr = {};

Level::Level(const std::string& svgPath, const std::string& texturePath):
	m_ScaleFactor{ 3.47f}
{
	m_Path = texturePath;
	SVGParser::GetVerticesFromSvgFile(svgPath,m_ColliderArr);

	m_PlatformsArr.push_back(new MovingPlatform{ "MovingPlatform.png",Vector2f{982.f,30.f},70.f,5.f });
	m_PlatformsArr.push_back(new FadeOutPlatform{ "FadeOutPlatform.png", Vector2f{1845.f,20.f},3,5 });
	m_PlatformsArr.push_back(new FadeOutPlatform{ "FadeOutPlatform.png", Vector2f{1910.f,20.f},3,5 });
}

Level::~Level()
{
	for (Platform* obj : m_PlatformsArr)
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

}
float Level::GetScaleFactor() const
{
	return m_ScaleFactor;
}