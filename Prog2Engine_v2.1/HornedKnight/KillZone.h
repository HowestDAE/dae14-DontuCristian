#pragma once
#include "DMGZone.h"

class KillZone final: public DMGZone
{
public:
	KillZone(const std::string& textPath, const Vector2f& pos, int rows, int columns, float frameDelay);

	void operator=(const KillZone&) = delete;
	void operator=(const KillZone&&) = delete;

	KillZone(const KillZone& obj) = delete;
	KillZone(const KillZone&& obj) = delete;
	~KillZone();

private:

};

