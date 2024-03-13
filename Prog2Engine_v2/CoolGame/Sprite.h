#pragma once
#include "Texture.h"
#include "Transform.h"
#include "utils.h"

class Sprite
{
public:
	//Constructor(s) and destructor
	Sprite(const std::string& texturePath, const Point2f& location,int rows, int columns, float frameDelay);

	~Sprite();

	// Member functions
	void Draw() const;
	void Update(float elapsedSec, const Point2f& location);

	void SetAnimation(int rowIdx);
	void Flip(bool x, bool y);

	float GetFrameWidth();
	float GetFrameHeight();


private:

	void ModifyTransform(const Vector2f& pos, float angle, const Vector2f& scale);

	Texture*	m_MyTexture;
	Point2f		m_Location;
	Transform*	m_TextureTransform;

	int			m_Rows, m_Columns;
	int			m_FrameWidth{ -1 }, m_FrameHeight{ -1 };
	float		m_FrameDelay;
	float		m_AccumulatedTime{};
	int			m_CurrentFrame{};
	int			m_RowIdx { 0 }, m_ColIdx { 0 };
};

