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
	void DrawWorld() const;

	Rectf GetViewRect();
	Point2f GetPosition();
	void SetTarget(const Point2f& target);

private:
	Camera();

	Point2f m_Target;
	Point2f m_Position;

	Rectf m_ViewRect;

	static Camera* m_Instance;
};