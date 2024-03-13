#include "pch.h"
#include "Player.h"

Player::Player(const Point2f& pos, const std::string& filePath, const Vector2f& velocity):
	m_isAlive	 {true},
	m_NrLives	 {7},
	m_Velocity	 {velocity},
	m_isOnGround {false},
	m_isFlipped	 {false}
{
	m_Position = pos;
	m_AttackRange = Circlef{ pos,15 };
	m_Spritesheet3x5 = new Sprite{ filePath, pos, 3, 5, 0.1f };
	SpriteManager::CreateSprite(m_Spritesheet3x5);
	m_Collider = Rectf{ pos.x - 20.f, pos.y - 50.f,40.f, 60.f };
}

Player::~Player()
{
	delete m_Spritesheet3x5;
}

void Player::Draw() const
{
	utils::SetColor(COL_COLOR);
	utils::DrawRect(m_Collider);

	m_Spritesheet3x5->Draw();
}

void Player::Update(float elapsedSec)
{
	MoveInput(elapsedSec);

	m_Position.x += m_Velocity.x * elapsedSec;
	m_Collider.left += m_Velocity.x * elapsedSec;

	m_Position.y += m_Velocity.y * elapsedSec;
	m_Collider.bottom += m_Velocity.y * elapsedSec;

	m_Spritesheet3x5->Update(elapsedSec, m_Position);
	//Temorary code for testing
	{
		if (m_Collider.bottom <= 10.f)
		{
			m_isOnGround = true;
		}
		if (m_isOnGround)
		{
			m_Velocity.y = 0.f;
		}
		else if (!m_isOnGround)
		{
			std::cout << m_isOnGround;
			m_Velocity.y -= GRAVITY.y * elapsedSec;
		}
	}
	if (m_Velocity.x > 0)
	{
		m_Spritesheet3x5->SetAnimation(2);
	}
	else if (m_Velocity.x < 0)
	{
		m_Spritesheet3x5->SetAnimation(2);
	}
	else
	{
		m_Spritesheet3x5->SetAnimation(0);
	}

}

void Player::SetIsAlive(bool myBool)
{
	m_isAlive = myBool;
}

void Player::MoveInput(float elapsedSec)
{
	m_Velocity.x = 0.f;

	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	if (pStates[SDL_SCANCODE_A] || pStates[SDL_SCANCODE_LEFT])
	{
		m_Velocity.x -= 300.f;
	}
	if (pStates[SDL_SCANCODE_D] || pStates[SDL_SCANCODE_RIGHT])
	{
		m_Velocity.x += 300.f;
	}


}

void Player::Jump(const SDL_KeyboardEvent& e)
{
	if (m_isOnGround)
	{
		switch (e.keysym.sym)
		{
		case SDLK_w:
		case SDLK_SPACE:
			m_Velocity.y = 600.f;
			m_isOnGround = false;
			std::cout << "Jump" << "\n";
			break;
		}
	}
}

void Player::Dash(const SDL_KeyboardEvent& e)
{
}

void Player::Attack(const SDL_MouseButtonEvent& e)
{
	if (SDL_BUTTON_LEFT)
	{
	}
}

int Player::GetNrLives()
{
	return m_NrLives;
}
