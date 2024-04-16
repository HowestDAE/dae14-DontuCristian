#pragma once
#include "TextureManager.h"
#include "utils.h"
#include <iostream>

class Sprite
{
public:
	//Constructor(s) and destructor
	Sprite(const std::string& texturePath, const Point2f& location,int rows, int columns, float frameDelay);

	~Sprite();
	Sprite(Sprite& obj) = default;
	Sprite& operator = (const Sprite& obj) = default;

	// Member functions
	void Draw() const;
	void Update(float elapsedSec, const Point2f& location);
	void Flip() const;

	void SetAnimation(int rowIdx);
	void ResetAnim();
	void SetIsFlipped(bool myBool);

	int	  GetFrameWidth();
	int	  GetFrameHeight();
	int	  GetRowIdx();
	int	  GetColIdx();

private:
	bool m_isFlipped;
	Point2f		m_Location;
	std::string m_Path;

	Rectf		m_SourceRect;
	int			m_Rows, m_Columns;
	int			m_FrameWidth{ -1 }, m_FrameHeight{ -1 };
	float		m_FrameDelay;
	float		m_AccumulatedTime{};
	int			m_CurrentFrame{};
	int			m_RowIdx { 0 }, m_ColIdx { 0 };
};

