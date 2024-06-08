#pragma once
#include <utils.h>
#include "Texture.h"
using namespace utils;

class StringSprite
{
public:
	// constructor(s) and destructor
	StringSprite(	const std::string& text, const std::string& fontPath,
					int size, const Color4f& color, const Vector2f& position );
	~StringSprite();

	// member functions
	void Draw();
	void SetPosition(const Vector2f& position);
	void Recreate(	const std::string& text);

private:

	// datamembers
	Texture* m_StringTexture;
	Vector2f	m_Position;
	std::string m_FontPath;
	int m_Size;
	Color4f m_Color;
};

