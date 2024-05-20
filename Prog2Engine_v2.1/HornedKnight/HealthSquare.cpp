#include "pch.h"
#include "HealthSquare.h"

HealthSquare::HealthSquare(const std::string& path, const Vector2f& pos, int rows, int col, float frameDelay):
	m_isFilled{true},
	m_Pos{pos}
{
	m_Sprite = new Sprite{ path,pos,rows,col,frameDelay };
}

HealthSquare::~HealthSquare()
{
	delete m_Sprite;
	m_Sprite = nullptr;
}

void HealthSquare::Update(float elapsedSec)
{
	m_Sprite->Update(elapsedSec, m_Pos);

	if(m_isFilled)
		m_Sprite->SetAnimation(1);
	else
		m_Sprite->SetAnimation(0);
}

void HealthSquare::Draw() const
{	
	m_Sprite->Draw();
}

bool HealthSquare::GetIsFilled()
{
	return m_isFilled;
}

void HealthSquare::SetIsFilled(bool myBool)
{
	m_isFilled = myBool;
}


