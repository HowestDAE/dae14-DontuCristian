#pragma once
#include "utils.h"
#include "GameVars.h"
#include <iostream>

class Camera
{
public:
	Camera(const Camera& obj) = delete;
	void operator=(const Camera&) = delete;

	static Camera* GetInstance();


	void Update(float elapsedSec,float zoom);

	Rectf GetViewRect();
	Vector2f GetPosition();
	void SetTarget(const Vector2f& target);

private:
	Camera();

	Vector2f m_Target;
	Vector2f m_Position;

	Rectf m_ViewRect;

	static Camera* m_Instance;
};