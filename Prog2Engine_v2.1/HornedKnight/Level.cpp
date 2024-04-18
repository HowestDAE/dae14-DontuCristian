#include "pch.h"
#include "Level.h"

std::vector<Point2f> Level::m_Collider = {};

Level::Level(const std::string& svgPath, const std::string& texturePath):
	m_ScaleFactor{ 3.47f}
{
	std::vector<std::vector<Point2f>> collider{};
	m_Path = texturePath;
	SVGParser::GetVerticesFromSvgFile(svgPath,collider);
	m_Collider = collider[0];

}

Level::~Level()
{
}
void Level::Update(float elapsedSec)
{
}
void Level::Draw() const
{
	TextureManager::GetInstance()->GetTexture(m_Path)->Draw();
	utils::SetColor(Color4f{ 0,1,0,1 });
	utils::DrawPolygon(m_Collider, true);	

		//std::cout << m_LevelCollider.size();
}
