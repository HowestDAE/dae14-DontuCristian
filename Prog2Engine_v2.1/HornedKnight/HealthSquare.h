#pragma once
#include "Sprite.h"
#include "utils.h"

class HealthSquare
{
public:
	HealthSquare(const std::string& path, const Vector2f& pos, int rows = { 2 }, int col = { 1 }, float frameDelay = { 0.f });

	~HealthSquare();

	void Update(float elapsedSec);

	void Draw() const;

	bool GetIsFilled();
	void SetIsFilled(bool myBool);

private:

	Vector2f m_Pos;

	Sprite* m_Sprite;
	bool   m_isFilled;
};

