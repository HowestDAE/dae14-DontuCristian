#include "pch.h"
#include "StringSprite.h"

StringSprite::StringSprite(const std::string& text, const std::string& fontPath,
	int size, const Color4f& color, const Vector2f& position) : 
	m_Position{position},
	m_FontPath{fontPath},
	m_Size{size},
	m_Color{color}
{
	m_StringTexture = new Texture{text,fontPath,size,color};
}

StringSprite::~StringSprite()
{
	delete m_StringTexture;
}

void StringSprite::Recreate(const std::string& text)
{
	delete m_StringTexture;

	m_StringTexture = new Texture{ text, m_FontPath, m_Size, m_Color };
}

Vector2f StringSprite::GetPosition()
{
	return m_Position;
}

void StringSprite::Draw()
{
	m_StringTexture->Draw(m_Position.ToPoint2f());
}

void StringSprite::SetPosition(const Vector2f& position)
{
	m_Position = position;
}

