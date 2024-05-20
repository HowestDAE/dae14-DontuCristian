#include "pch.h"
#include "TextureManager.h"

TextureManager* TextureManager::m_Instance = nullptr;

TextureManager::TextureManager()
{
    //Creating empty texture so you can always run

}

TextureManager::~TextureManager()
{
    //deletes the hashmap
    //No auto :(
    for (std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<const std::string, Texture*>>>> iterator = m_MyHashMap.begin(); iterator != m_MyHashMap.end();)
    {
        delete iterator->second;
        iterator->second = nullptr;
        iterator = m_MyHashMap.erase(iterator);
    }

}

TextureManager* TextureManager::GetInstance()
{
	m_Instance = (m_Instance != nullptr) ? m_Instance : new TextureManager();
	return m_Instance;
}

void TextureManager::DeleteSingleton()
{
    delete m_Instance;
}

Texture* TextureManager::GetTexture(const std::string& texturePath)
{
    //No auto :/
    std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<const std::string, Texture*>>>> iterator = m_MyHashMap.find(texturePath);

    //returns texture if it exists
    if (iterator != m_MyHashMap.end())
    {
        return m_MyHashMap.at(texturePath);
    }

    //creates texture if it doesn't exist
    else
    {
        Texture* newTexture = new Texture(texturePath);
        if (newTexture->IsCreationOk())
        {
            m_MyHashMap.insert({ texturePath, newTexture });
            return m_MyHashMap.at(texturePath);
        }
        //returns empty texture if the creation of the texture fails
        else
        {
            std::cout << "Texture creation has failed! name: " << texturePath << std::endl;

            return m_MyHashMap.at("Null.png");
        }
    }
}
