#include "pch.h"
#include "Level.h"
#include "Camera.h"
#include "GameVars.h"


Level::Level(const std::string& svgPath, const std::string& texturePath)
{
	m_Texture = new Texture{texturePath};
	SVGParser::GetVerticesFromSvgFile(svgPath,m_LevelCollider);
	m_ScaleFactor = SCREEN_HEIGHT / m_Texture->GetHeight();
	std::cout << m_ScaleFactor << "\n";
}

Level::~Level()
{
	delete m_Texture;
}
void Level::Update(float elapsedSec)
{
}
void Level::Draw() const
{
	Rectf dstRect { 0.f,0.f,m_Texture->GetWidth(),m_Texture->GetHeight() };

		m_Texture->Draw(dstRect);

		utils::SetColor(Color4f{ 0,1,0,1 });
		glPushMatrix();
		{
			//glTranslatef(297.f, 120.f, 0.f);
			for (int idx{}; idx < m_LevelCollider.size(); idx++)
			{
				utils::DrawPolygon(m_LevelCollider[idx], false);
			}
		}glPopMatrix();

}
