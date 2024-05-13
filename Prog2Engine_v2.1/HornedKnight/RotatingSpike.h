#pragma once
#include "Spike.h"

class RotatingSpike final:public Spike
{
public:
	RotatingSpike();

	void operator=(const RotatingSpike&) = delete;
	void operator=(const RotatingSpike&&) = delete;

	RotatingSpike(const RotatingSpike& obj) = delete;
	RotatingSpike(const RotatingSpike&& obj) = delete;

	~RotatingSpike();

	void Update();
	void Draw() const;
private:

	Sprite* m_Chain;
};

