#pragma once
#include "SVGParser.h"
#include "Texture.h"
#include "utils.h"
#include "Player.h"
class Level
{
public:
	Level(const std::string& svgPath, const std::string& texturePath);
	~Level();

	void Update(float elapsedSec);
	void Draw() const;

	std::vector<std::vector<Point2f>> GetCollider();

	float m_ScaleFactor;
private:

	std::string m_TexturePath;
	std::vector<std::vector<Point2f>> m_LevelCollider;
};

