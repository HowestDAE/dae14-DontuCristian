#pragma once
#include "utils.h"
#include "DMGZone.h" 

class Spike: public DMGZone
{
public:

	Spike(const std::string& textPath, const Vector2f& pos, int rows = { 1 }, int columns = { 1 }, float frameDelay = { 0.f });

	void operator=(const Spike&) = delete;
	void operator=(const Spike&&) = delete;

	Spike(const Spike& obj) = delete;
	Spike(const Spike&& obj) = delete;
	virtual ~Spike();

	void Update(float elapsedSec);

private:

	float m_AccumulatedTime{};

};


