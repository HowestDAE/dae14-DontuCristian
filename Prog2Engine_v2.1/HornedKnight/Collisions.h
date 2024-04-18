#pragma once
#include "utils.h"
#include "Level.h"
#include "Player.h"

class Collisions
{
public:
	static void CheckPlayerCollision(float elapsedSec, std::vector<Point2f> poly);

	static utils::HitInfo m_HitInfo;
private:

};

