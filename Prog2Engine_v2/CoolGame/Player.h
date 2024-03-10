#pragma once
#include "Texture.h"
class Player
{
public:
	Player(const Point2f& pos, const std::string& filePath);
	~Player();

	void Draw() const;

	void Update();
	
	void SetIsAlive(bool myBool);

	int GetNrLives();

private:

	bool m_isAlive;

	int m_NrLives;

	Texture* m_PlSpritesheet;
	Rectf m_Collider;
	Point2f m_Position;

	Circlef m_AttackRange;
};

