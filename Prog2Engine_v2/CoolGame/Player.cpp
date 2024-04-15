#include "pch.h"
#include "Player.h"

Player::Player(	const Point2f& pos, float speed, float jmpPower, const std::string& filePath, Level* levelPtr,
				int rows, int columns, float frameDelay) :
	m_isAlive	 {true},
	m_NrLives	 {7},
	m_Velocity	 {0.f,0.f},
	m_isOnGround {false},
	m_isFlipped	 {false},
	m_PlayerState{PlayerState::idle},
	m_Speed		 {speed},
	m_JmpPower	 {jmpPower}
{
	m_LevelPtr = levelPtr;
	m_Position = pos;
	m_AttackRange = Circlef{ pos, 15 };
	m_Spritesheet8x5 = new Sprite{ filePath,Point2f{pos.x,pos.y}, rows, columns, frameDelay };
	m_Collider = Rectf{ pos.x-7.f , pos.y-8.f,14.f, 20.f };
}

Player::~Player()
{
	delete m_Spritesheet8x5;
}

void Player::Draw() const
{
	utils::SetColor(COL_COLOR);
	utils::DrawRect(m_Collider);

	m_Spritesheet8x5->Draw();
}

void Player::Update(float elapsedSec)
{
	ChangeAnimation();

	MoveInput();

	m_Position.x += m_Velocity.x * elapsedSec;
	m_Collider.left = m_Position.x - m_Collider.width / 2;

	m_Position.y += m_Velocity.y * elapsedSec;
	m_Collider.bottom = m_Position.y - (m_Collider.height / 2 + 5.f);

	//Setting the player animation based on velocity
	ChangeStates();
	m_Spritesheet8x5->Update(elapsedSec, m_Position);

}

void Player::SetIsAlive(bool myBool)
{
	m_isAlive = myBool;
}

void Player::MoveInput()
{
	m_Velocity.x = 0.f;

	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	if (pStates[SDL_SCANCODE_A] || pStates[SDL_SCANCODE_LEFT])
	{
		m_isFlipped = true;
		m_Velocity.x = -m_Speed;
	}
	if (pStates[SDL_SCANCODE_D] || pStates[SDL_SCANCODE_RIGHT])
	{
		m_isFlipped = false;
		m_Velocity.x = m_Speed;
	}


}

void Player::ChangeStates()
{
	if (m_PlayerState != PlayerState::dash)
	{
		if (m_PlayerState != PlayerState::attack)
		{
			if (!m_isOnGround)
			{
				if (m_Velocity.y > 0)
				{
					m_PlayerState = PlayerState::jump;
				}
				else
				{
					m_PlayerState = PlayerState::fall;
				}
			}
			if (m_isOnGround)
			{
				if (m_Velocity.x != 0)
				{
					m_PlayerState = PlayerState::walking;
				}
				else
				{
					m_PlayerState = PlayerState::idle;
				}
			}
		}
	}

	//End the attack animation
	if (m_Spritesheet8x5->GetColIdx() == 4 && m_PlayerState == PlayerState::attack)
	{
		m_PlayerState = PlayerState::idle;
	}
}

void Player::Jump(const SDL_KeyboardEvent& e)
{
	if (m_isOnGround)
	{
		if(e.keysym.sym == SDLK_SPACE)
		{
			m_Velocity.y = m_JmpPower;
			m_isOnGround = false;
		}
	}
}

void Player::Dash(const SDL_KeyboardEvent& e)
{
	if (e.keysym.sym == SDLK_LSHIFT)
	{
		m_PlayerState = PlayerState::dash;
		if (m_isFlipped)
		{
			m_Position.x -= 100;
		}
		else
		{
			m_Position.x += 100;
		}
	}
}

void Player::Attack(const SDL_MouseButtonEvent& e)
{
	if (e.button==SDL_BUTTON_LEFT)
	{
		m_Spritesheet8x5->ResetAnim();
		m_PlayerState = PlayerState::attack;
	}
}

void Player::HandleCollision()
{
	ColDir colDirection = {Collisions::IsRectInPoly(this->m_Collider, m_LevelPtr->GetCollider())};

	switch (colDirection)
	{
	case ColDir::bottom: m_isOnGround = true;
		break;
	case ColDir::top: m_Velocity.y = 0.f;
}
	{
		if (m_Collider.bottom <= 5.f)
		{
			m_isOnGround = true;
		}
		if (m_isOnGround)
		{
			m_Velocity.y = 0.f;
		}
		else if (!m_isOnGround)
		{
			m_Velocity.y -= GRAVITY.y;
		}
	}
}

void Player::ChangeAnimation()
{
	m_Spritesheet8x5->SetIsFlipped(m_isFlipped);

	m_Spritesheet8x5->SetAnimation(int(m_PlayerState));

}

int Player::GetNrLives()
{
	return m_NrLives;
}

Point2f Player::GetPosition()
{
	return m_Position;
}
