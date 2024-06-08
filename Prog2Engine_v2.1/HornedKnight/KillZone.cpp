#include "pch.h"
#include "KillZone.h"

KillZone::KillZone(const std::string& textPath, const Vector2f& pos, int rows, int columns, float frameDelay):
	DMGZone(textPath,pos,rows,columns,frameDelay)
{
}

KillZone::~KillZone()
{
}

