#pragma once
#include "utils.h"
#include "Sprite.h"

class DMGZone
{
public:

	DMGZone(const std::string& textPath, const Vector2f& pos, int rows = { 1 }, int columns = { 1 }, float frameDelay = {0.f});

	void operator=(const DMGZone&) = delete;
	void operator=(const DMGZone&&) = delete;

	DMGZone(const DMGZone& obj) = delete;
	DMGZone(const DMGZone&& obj) = delete;
	virtual ~DMGZone();

	virtual void Update(float elapsedSec);
	virtual void Draw() const;

	Rectf GetCollider() const;

protected:

	Vector2f	m_Pos;
	Rectf		m_Collider;
	Sprite*		m_Sprite;
};

