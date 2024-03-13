#include "pch.h"
#include "Sprite.h"

Sprite::Sprite(const std::string& texturePath, const Point2f& location, int rows, int columns, float frameDelay) :
	m_Rows{ rows },
	m_Columns{ columns },
	m_FrameDelay{ frameDelay }
{
	m_MyTexture = new Texture{texturePath};
    m_TextureTransform = new Transform{ Vector2f{0.f,0.f},0.f,Vector2f{0.f,0.f} };

	m_FrameWidth = m_MyTexture->GetWidth() / m_Columns;
	m_FrameHeight = m_MyTexture->GetHeight() / m_Rows;

	m_Location = Point2f{ location.x - m_FrameWidth/2 , location.y - m_FrameHeight/2 };
}

Sprite::~Sprite()
{
	delete m_MyTexture;
}

void Sprite::Draw() const
{
	const Rectf sourceRect{ float(m_ColIdx * m_FrameWidth),
							float(m_RowIdx * m_FrameHeight),
							float(m_FrameWidth),
							float(m_FrameHeight) };

	utils::DrawRect(sourceRect);
	m_MyTexture->Draw(m_Location, sourceRect);
}

void Sprite::Update(float elapsedSec, const Point2f& location)
{
	m_Location = Point2f{location.x - m_FrameWidth/2, location.y - m_FrameHeight/2};

	m_ColIdx = m_CurrentFrame % m_Columns;

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
void Sprite::SetAnimation(int rowIdx)
{
	m_RowIdx = rowIdx;
}
void Sprite::Flip(bool x,bool y)
{
	if(x)
	ModifyTransform(Vector2f{ 0.f,0.f }, 0.f, Vector2f{ -1.f ,1.f  });
	if(y)
	ModifyTransform(Vector2f{ 0.f,0.f }, 0.f, Vector2f{ 1.f ,-1.f });
	m_TextureTransform->ApplyTransformation();
}
void Sprite::ModifyTransform(const Vector2f& pos, float angle, const Vector2f& scale)
{
	m_TextureTransform->Position = pos;
	m_TextureTransform->Rotation = angle;
	m_TextureTransform->Scale = scale;
}
float Sprite::GetFrameWidth()
{
	return m_FrameWidth;
}
float Sprite::GetFrameHeight()
{
	return m_FrameHeight;
}
