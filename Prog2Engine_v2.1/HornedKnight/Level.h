#pragma once
#include "SVGParser.h"
#include "Sprite.h"
#include "utils.h"
#include "Camera.h"
#include "GameVars.h"
class Level
{
public:
	Level(const std::string& svgPath, const std::string& texturePath);
	~Level();

	void Update(float elapsedSec);
	void Draw() const;
	
	static  std::vector<Point2f> m_Collider;

	float m_ScaleFactor;
private:

	std::string m_Path;
};

