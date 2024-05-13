#pragma once
#include "Platform.h"
#include <iostream>

class FadeOutPlatform final:public Platform
{
public:
	FadeOutPlatform(const std::string& textPath, const Vector2f& pos, int rows, int columns);

	void Update(float elapsedSec);
	void SetCollision(bool myBool);

	bool	GetIsInteractable();
	Sprite* GetSprite();
	
private:
	//CONSTANTS
	static const float INTERACTABLE_TIME;
	static const float FADE_TIME;
	static const float RESET_TIME;

	//Member variables
	float m_AccumulatedTime;
	float m_PresetHeight; //this variable is used to return the platform to its preset height when resetting it

	bool m_isInteractable;  //decides if the player can interact with the platform
	bool m_Collision;
};

