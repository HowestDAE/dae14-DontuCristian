#include "pch.h"
#include "Player.h"

Player::Player(const Vector2f& pos, float speed, float jmpPower, const std::string& filePath,
	int rows, int columns, float frameDelay):
	m_isAlive	 {true},
	m_NrLives	 {7},
	m_Velocity	 {0.f,0.f},
	m_isOnGround {false},
	m_isFlipped	 {false},
	m_PlayerState{PlayerState::idle},
	m_Speed		 {speed},
	m_JmpPower	 {jmpPower},
	m_WallHit	 {false}
{
	m_Position = pos;
	m_AttackRange = Circlef{ Point2f{pos.x,pos.y }, 15
};
	m_Spritesheet = new Sprite{ filePath,pos, rows, columns, frameDelay };
	m_Collider = Rectf{ pos.x-7.f , pos.y-8.f,14.f, 20.f };
}

Player::~Player()
{
	delete m_Spritesheet;
}

void Player::Draw() const
{
	const Vector2f nextPos{ m_Position.x + m_Velocity.x * m_ElapsedSec,
								m_Position.y + m_Velocity.y * m_ElapsedSec };

	const Rectf nextCollider{ m_Collider.left + m_Velocity.x * m_ElapsedSec,
							  m_Collider.bottom + m_Velocity.y * m_ElapsedSec,
							  m_Collider.width,
							  m_Collider.height };



	//Points from player
	const Point2f bottomLeft{ m_Collider.left, m_Collider.bottom };
	const Point2f topLeft{ m_Collider.left, m_Collider.bottom + m_Collider.height };
	const Point2f topRight{ m_Collider.left + m_Collider.width, m_Collider.bottom + m_Collider.height };
	const Point2f bottomRight{ m_Collider.left + m_Collider.width, m_Collider.bottom };

	//Next points from player
	const Point2f nextBottomLeft{ nextCollider.left, nextCollider.bottom };
	const Point2f nextTopLeft{ nextCollider.left, nextCollider.bottom + nextCollider.height };
	const Point2f nextTopRight{ nextCollider.left + nextCollider.width, nextCollider.bottom + nextCollider.height };
	const Point2f nextBottomRight{ nextCollider.left + nextCollider.width, nextCollider.bottom };

	utils::DrawLine(bottomLeft, nextBottomLeft);
	utils::DrawLine(bottomRight, nextBottomRight);
	utils::DrawLine(topLeft, nextTopLeft);
	utils::DrawLine(topRight, nextTopRight);


	utils::SetColor(COL_COLOR);

	utils::DrawRect(m_Collider);

	m_Spritesheet->Draw();
}

void Player::Update(float elapsedSec)
{
	m_ElapsedSec = elapsedSec;
	ChangeAnimation();

	MoveInput();

	//Temorary code for testing
	if (!m_isOnGround)
	{
		m_Velocity.y -= GRAVITY.y * elapsedSec;
	}
	//Half working collisions, gotta fix them
	HandleCollision(elapsedSec, Level::m_Collider);

	if (m_PlayerState != PlayerState::dash)
	{
		m_Position.x += m_Velocity.x * elapsedSec;
		m_Position.y += m_Velocity.y * elapsedSec;
	}
	
	m_Collider.left = m_Position.x - m_Collider.width / 2;
	m_Collider.bottom = m_Position.y - (m_Collider.height / 2 + 5.f);
	

	//Setting the player animation based on velocity
	ChangeStates();
	m_Spritesheet->Update(elapsedSec, m_Position);

	//if (m_PlayerState == PlayerState::dash)
	//{
	//
	//	Vector2f dashVelocity{ cosf((m_DashAngle *float(M_PI))/180) * DASH_SPEED,
	//					sinf((m_DashAngle * float(M_PI)) / 180) * DASH_SPEED };
	//
	//	m_Position += dashVelocity * elapsedSec;
	//}
}

void Player::SetIsAlive(bool myBool)
{
	m_isAlive = myBool;
}

void Player::MoveInput()
{
	m_Velocity.x = 0.f;

	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	if (pStates[SDL_SCANCODE_A])
	{
		m_isFlipped = true;
		m_Velocity.x = -m_Speed;
	}
	if (pStates[SDL_SCANCODE_D])
	{
		m_isFlipped = false;
		m_Velocity.x = m_Speed;
	//	if (m_PlayerState == PlayerState::dash)
	//	{
	//		m_DashAngle = 0.f;
	//		if (pStates[SDL_SCANCODE_W])
	//		{
	//			m_DashAngle = 45.f;
	//		}
	//   }
	}
	//if (pStates[SDL_SCANCODE_W])
	//{
	//	if (m_PlayerState == PlayerState::dash)
	//	{
	//		m_DashAngle = 90.f;
	//	}
	//}
}

void Player::ChangeStates()
{
	if (m_PlayerState != PlayerState::dash)
	{
		if (m_PlayerState != PlayerState::attack)
		{
			if (!m_isOnGround)
			{
				if (m_Velocity.y >= 0.f)
				{
					m_PlayerState = PlayerState::jump;
				}
				else if(m_Velocity.y <= 0.f)
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
	if (m_Spritesheet->GetColIdx() == 4 && m_PlayerState == PlayerState::attack)
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
	//if (e.keysym.sym == SDLK_LSHIFT)
	//{
	//	m_PlayerState = PlayerState::dash;
	//	Vector2f dashVelocity { cosf((m_DashAngle*180)/float(M_PI))* DASH_SPEED,
	//z							-sinf((m_DashAngle*180)/float(M_PI))* DASH_SPEED};
	//
	//	m_Position += dashVelocity;
	//}
}

void Player::Attack(const SDL_MouseButtonEvent& e)
{
	if (e.button==SDL_BUTTON_LEFT)
	{
		m_Spritesheet->ResetAnim();
		m_PlayerState = PlayerState::attack;
	}
}

void Player::HandleCollision(float elapsedSec, std::vector<Point2f> poly)
{
	const Vector2f nextPos{ m_Position.x + m_Velocity.x * elapsedSec,
								m_Position.y + m_Velocity.y * elapsedSec };

	const Rectf nextCollider{ m_Collider.left + m_Velocity.x * elapsedSec,
							  m_Collider.bottom + m_Velocity.y * elapsedSec,
							  m_Collider.width,
							  m_Collider.height };



	//Points from player
	const Point2f bottomLeft{ m_Collider.left, m_Collider.bottom };
	const Point2f topLeft{ m_Collider.left, m_Collider.bottom + m_Collider.height };
	const Point2f topRight{ m_Collider.left + m_Collider.width, m_Collider.bottom + m_Collider.height };
	const Point2f bottomRight{ m_Collider.left + m_Collider.width, m_Collider.bottom };

	//Next points from player
	const Point2f nextBottomLeft{ nextCollider.left, nextCollider.bottom };
	const Point2f nextTopLeft{ nextCollider.left, nextCollider.bottom + nextCollider.height };
	const Point2f nextTopRight{ nextCollider.left + nextCollider.width, nextCollider.bottom + nextCollider.height };
	const Point2f nextBottomRight{ nextCollider.left + nextCollider.width, nextCollider.bottom };

	utils::HitInfo infoBottomLeft{};
	utils::HitInfo infoBottomRight{};
	utils::HitInfo infoTopLeft{};
	utils::HitInfo infoTopRight{};

	// Check collision with the world

	const bool hitBottomLeft{ Raycast(Level::m_Collider, bottomLeft, nextBottomLeft, infoBottomLeft) };
	const bool hitBottomRight{ Raycast(Level::m_Collider, bottomRight, nextBottomRight, infoBottomRight) };
	const bool hitTopLeft{ Raycast(Level::m_Collider, topLeft, nextTopLeft, infoTopLeft) };
	const bool hitTopRight{ Raycast(Level::m_Collider, topRight, nextTopRight, infoTopRight) };


	float avgCount{ 0 };
	Vector2f avgNormal{ Vector2f() };
	float avgLambda{ 0.f };

	// Properly calculate the averages
	if (hitBottomLeft)
	{
		avgNormal += infoBottomLeft.normal;
		avgLambda += infoBottomLeft.lambda;
		++avgCount;
	}

	if (hitBottomRight)
	{
		avgNormal += infoBottomRight.normal;
		avgLambda += infoBottomRight.lambda;
		++avgCount;
	}

	if (hitTopLeft)
	{
		avgNormal += infoTopLeft.normal;
		avgLambda += infoTopLeft.lambda;
		++avgCount;
	}

	if (hitTopRight)
	{
		avgNormal += infoTopRight.normal;
		avgLambda += infoTopRight.lambda;
		++avgCount;
	}

	if (avgCount != 0.f)
	{
		avgNormal /= avgCount;
		avgLambda /= avgCount;
	}

	if (!utils::IsPointInPolygon(bottomLeft, poly) || !utils::IsPointInPolygon(topLeft, poly) || !utils::IsPointInPolygon(topRight, poly) || !utils::IsPointInPolygon(bottomRight, poly)) 
	{
		if (!utils::IsPointInPolygon(topLeft, poly) || !utils::IsPointInPolygon(topRight, poly))
			m_Velocity.y = -1.f;
		if (!utils::IsPointInPolygon(bottomLeft, poly) || !utils::IsPointInPolygon(bottomRight, poly)) 
			m_Velocity.y = 0.f;
	}

	if (infoBottomLeft.normal.y > 0.f && infoBottomRight.normal.y > 0.f)
	{
		m_isOnGround = true;
	}
	else
	{
		m_isOnGround = false;
	}


	std::cout << avgNormal.y << "\n";
	if (m_isOnGround)
	{
		m_Collider.bottom = infoBottomLeft.intersectPoint.y;
		m_Velocity.y = 5.f;
	}

		//Sliding collision
		if (hitBottomLeft||hitBottomRight||hitTopRight||hitTopLeft)
		{
			m_WallHit = true;
		}
		else
		{
			m_WallHit = false;
		}

		if (m_WallHit)
		{
			m_Velocity.x = 0.f;
		}

		//Wall collisions
		if (hitBottomLeft || hitTopLeft)
		{
			m_Velocity.x = 0.f;
		}
		else if (hitBottomRight || hitTopRight)
		{
			m_Velocity .x = 0.f;
		}
}

void Player::ChangeAnimation()
{
	m_Spritesheet->SetIsFlipped(m_isFlipped);

	m_Spritesheet->SetAnimation(int(m_PlayerState));

}

int Player::GetNrLives()
{
	return m_NrLives;
}

Vector2f Player::GetPosition()
{
	return m_Position;
}

Vector2f Player::GetVelocity()
{
	return m_Velocity;
}
