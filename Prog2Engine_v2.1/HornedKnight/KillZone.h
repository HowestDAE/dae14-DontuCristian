#pragma once
#include "DMGZone.h"

class KillZone final: public DMGZone
{
public:
	KillZone();

	void operator=(const KillZone&) = delete;
	void operator=(const KillZone&&) = delete;

	KillZone(const KillZone& obj) = delete;
	KillZone(const KillZone&& obj) = delete;
	~KillZone();

	void Update();
	void Draw() const;

private:

};

