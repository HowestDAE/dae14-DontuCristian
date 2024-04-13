#pragma once
#include "utils.h"
#include "Level.h"
#include "Player.h"
enum class ColDir
{
	top,
	bottom,
	left,
	right
};

class Collisions
{
public:

	static ColDir IsRectInPoly(const Rectf& rect, const std::vector<Point2f>& poly);

private:

	Player* m_PlayerPtr;
	Level*	m_LevelPtr;

};

