#pragma once
#include "utils.h"
#include "GameVars.h"
#include <iostream>

class Camera
{
public:
	//Rule of 3
	~Camera();
	Camera(const Camera& obj) = delete;
	void operator=(const Camera&) = delete;

	//Gets the instance of my camera
	static Camera* GetInstance();

	void Update(float elapsedSec,float zoom);

	Rectf GetViewRect() const;
	Vector2f GetPosition() const;

	void SetTarget(const Vector2f& target);

private:
	Camera();

	Vector2f m_Target;
	Vector2f m_Position;

	Rectf m_ViewRect;

	static Camera* m_Instance;
};