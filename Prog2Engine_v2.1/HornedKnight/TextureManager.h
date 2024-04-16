#pragma once
#include "Texture.h"
#include <iostream>
#include <unordered_map>
class TextureManager
{
public:
	TextureManager(const TextureManager& obj) = delete;
	void operator=(const TextureManager&) = delete;

	~TextureManager();

	static TextureManager* GetInstance();

	Texture* GetTexture(const std::string& texturePath);
private:
	TextureManager();

	static TextureManager* m_Instance;

	std::unordered_map<std::string, Texture*> m_MyHashMap;
};

