#include "pch.h"
#include "Camera.h"

Camera* Camera::m_Instance = nullptr;

Camera::Camera() :
	m_ViewRect{ 0.f,0.f,SCREEN_WIDTH,SCREEN_HEIGHT }
{

}

Camera* Camera::GetInstance()
{
	m_Instance = (m_Instance != nullptr) ? m_Instance : new Camera;
	return m_Instance;
}
void Camera::Update(float elapsedSec,float zoom)
{
		m_ViewRect.left = m_Target.x - (SCREEN_WIDTH / 2)/zoom;
		m_ViewRect.bottom = m_Target.y - 50.f/zoom;	

		m_ViewRect.left = (m_ViewRect.left < 0) ? 0 : m_ViewRect.left;
		m_ViewRect.bottom = (m_ViewRect.bottom < 0) ? 0 : m_ViewRect.bottom;
		
		//m_ViewRect.left = (m_ViewRect.left > 2*SCREEN_WIDTH - m_ViewRect.width) ? 2 * SCREEN_WIDTH - m_ViewRect.width : m_ViewRect.left;
		m_ViewRect.bottom = (m_ViewRect.bottom > SCREEN_HEIGHT - m_ViewRect.height) ? SCREEN_HEIGHT - m_ViewRect.height : m_ViewRect.bottom;
		m_Position = Point2f{m_ViewRect.left * zoom, m_ViewRect.bottom * zoom};
}
Rectf Camera::GetViewRect()
{
	return m_ViewRect;
}

Point2f Camera::GetPosition()
{
	return m_Position;
}

void Camera::SetTarget(const Point2f& target)
{
	m_Target = target;
}
