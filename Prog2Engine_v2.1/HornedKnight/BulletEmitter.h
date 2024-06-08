#pragma once
#include "Bullet.h"
#include "utils.h"


class BulletEmitter
{
public:
	BulletEmitter(const Vector2f& pos, const Vector2f& direction, float firstBulletDelay);

	//Rule of 5
	void operator=(const BulletEmitter&) = delete;
	void operator=(const BulletEmitter&&) = delete;

	BulletEmitter(const BulletEmitter& obj) = delete;
	BulletEmitter(const BulletEmitter&& obj) = delete;
	~BulletEmitter();

	void Draw() const;
	void Update(float elapsedSec);

	void Emit(float elapsedSec,const std::string& textPath);
	void Shoot(const std::string& textPath);

	void DestroyBullet();

	static std::vector <Bullet*> m_BulletArr;
private:

	//CONSTANTS
	const float EMISSION_DELAY{ 2.f };

	//Members
	float m_AccumulatedTime;
	Vector2f m_Pos;
	Vector2f m_Dir;

};

