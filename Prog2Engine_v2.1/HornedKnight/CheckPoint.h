#pragma once
#include "utils.h"
#include "Sprite.h"
class CheckPoint
{
public:
	CheckPoint(const std::string& textPath, const Vector2f& pos, int rows = { 2 }, int columns = { 9 }, float frameDelay = {0.2f});

	//Rule of 5
	void operator= (const CheckPoint&) = delete;
	void operator= (const CheckPoint&&) = delete;
	CheckPoint(const CheckPoint& obj) = delete;
	CheckPoint(const CheckPoint&& obj) = delete;

	~CheckPoint();

	void Update(float elapsedSec);
	void Draw();

	Rectf	 GetCollider() const;
	Vector2f GetPosition() const;
	bool	 GetIsActive() const;

	void SetActive(bool myBool);


private:

	//Members
	bool m_isActive;

	Sprite* m_Sprite;

	Rectf	 m_Collider;
	Vector2f m_Pos;
};

