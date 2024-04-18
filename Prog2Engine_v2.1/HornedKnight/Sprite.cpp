#include "pch.h"
#include "Sprite.h"

Sprite::Sprite(const std::string& texturePath, const Vector2f& location, int rows, int columns, float frameDelay) :
	m_Rows{ rows },
	m_Columns{ columns },
	m_FrameDelay{ frameDelay },
	m_isFlipped{false},
	m_Path{texturePath}
{
	TextureManager::GetInstance()->GetTexture(texturePath);

	m_FrameWidth = int(TextureManager::GetInstance()->GetTexture(texturePath)->GetWidth()) / m_Columns;
	m_FrameHeight = int(TextureManager::GetInstance()->GetTexture(texturePath)->GetHeight()) / m_Rows;

	m_Location = Vector2f{ location.x - m_FrameWidth/2 , location.y - m_FrameHeight/2 };
}

Sprite::~Sprite()
{
	delete TextureManager::GetInstance()->GetTexture(m_Path);
}

void Sprite::Draw() const
{
	//utils::DrawRect(m_SourceRect);

	if (m_isFlipped)
	{
		Flip();
	}
	else
	{
		TextureManager::GetInstance()->GetTexture(m_Path)->Draw(Point2f{m_Location.x,m_Location.y}, m_SourceRect);
	}
}

void Sprite::Update(float elapsedSec, const Vector2f& location)
{
	//Updateing the SourceRect
	m_SourceRect = Rectf{	float(m_ColIdx * m_FrameWidth),
							float(m_RowIdx * m_FrameHeight),
							float(m_FrameWidth),
							float(m_FrameHeight) };

	m_Location.x = location.x - m_FrameWidth / 2;
	m_Location.y = location.y - m_FrameHeight / 2;

	//Update the column index
	m_ColIdx = m_CurrentFrame % m_Columns;

	//Time counter to constrol the framerate
	m_AccumulatedTime += elapsedSec;

	if (m_AccumulatedTime > m_FrameDelay)
	{
		++m_CurrentFrame;
		if (m_CurrentFrame >= m_Rows * m_Columns)
		{
			m_CurrentFrame = 0;
		}
		m_AccumulatedTime -= m_FrameDelay;
	}
}
void Sprite::Flip() const
{
	glPushMatrix();
		glTranslatef(-m_Location.x, -m_Location.y, 0);
		glScalef(-1, 1, 1);
		glTranslatef(-m_Location.x - m_FrameWidth, m_Location.y, 0);
		TextureManager::GetInstance()->GetTexture(m_Path)->Draw(Point2f{ -m_Location.x , m_Location.y }, m_SourceRect);
	glPopMatrix();
}
void Sprite::SetIsFlipped(bool myBool)
{
	m_isFlipped = myBool;
}
void Sprite::SetAnimation(int rowIdx)
{
	m_RowIdx = rowIdx;
}
void Sprite::ResetAnim()
{
	m_ColIdx = 0;
	m_CurrentFrame = 0;
}
int Sprite::GetFrameWidth()
{
	return m_FrameWidth;
}
int Sprite::GetFrameHeight()
{
	return m_FrameHeight;
}

int Sprite::GetRowIdx()
{
	return m_RowIdx;
}

int Sprite::GetColIdx()
{
	return m_ColIdx;
}
