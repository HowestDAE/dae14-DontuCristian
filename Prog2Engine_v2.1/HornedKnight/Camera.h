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
	static void DeleteSingleton();

	void Update(float elapsedSec,float zoom);

	void CameraShake();

	Rectf GetViewRect() const;
	Vector2f GetPosition() const;

	void SetTarget(const Vector2f& target);

private:
	Camera();

	//CONSTANTS
	const float MAX_SHAKE_TIME { 0.3f };

	//Member variables
	bool m_CameraShake{false};
	float m_CameraShakeTime{};

	Vector2f m_Target;
	Vector2f m_Position;

	Rectf m_ViewRect;

	static Camera* m_Instance;
};