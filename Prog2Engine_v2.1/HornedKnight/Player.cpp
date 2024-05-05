#include "pch.h"
#include "Player.h"

Player::Player(const Vector2f& pos, const std::string& filePath,
	int rows, int columns, float frameDelay):
	m_isAlive			{true},
	m_NrLives			{7},
	m_Velocity			{0.f,0.f},
	m_isOnGround		{false},
	m_isFlipped			{false},
	m_PlayerState		{PlayerState::idle},
	m_WallHit			{false}
{
	m_Position = pos;
	m_AttackRange = Circlef{ Point2f{pos.x,pos.y }, 15
};
	m_Spritesheet = new Sprite{ filePath,pos, rows, columns, frameDelay };
	m_Collider = Rectf{ pos.x-5.f , pos.y-16.f,10.f, 19.f };
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
	const Point2f bottomMidRight{ m_Collider.left + m_Collider.width, m_Collider.bottom + m_Collider.height / 2 };
	const Point2f bottomMidLeft{ m_Collider.left, m_Collider.bottom + m_Collider.height / 2 };

	const Point2f bottomLeft{ m_Collider.left, m_Collider.bottom };
	const Point2f topLeft{ m_Collider.left, m_Collider.bottom + m_Collider.height };
	const Point2f topRight{ m_Collider.left + m_Collider.width, m_Collider.bottom + m_Collider.height };
	const Point2f bottomRight{ m_Collider.left + m_Collider.width, m_Collider.bottom };

	//Next points from player
	const Point2f nextMidLeft{ nextCollider.left, nextCollider.bottom + nextCollider.height / 2 };
	const Point2f nextMidRight{ nextCollider.left + nextCollider.width, nextCollider.bottom + nextCollider.height / 2 };

	const Point2f nextBottomLeft{ nextCollider.left, nextCollider.bottom };
	const Point2f nextTopLeft{ nextCollider.left, nextCollider.bottom + nextCollider.height };
	const Point2f nextTopRight{ nextCollider.left + nextCollider.width, nextCollider.bottom + nextCollider.height };
	const Point2f nextBottomRight{ nextCollider.left + nextCollider.width, nextCollider.bottom };

	utils::DrawLine(bottomLeft, nextBottomLeft);
	utils::DrawLine(bottomRight, nextBottomRight);
	utils::DrawLine(topLeft, nextTopLeft);
	utils::DrawLine(topRight, nextTopRight);

	utils::DrawLine(bottomMidLeft, nextMidLeft);
	utils::DrawLine(bottomMidRight, nextMidRight);


	utils::SetColor(COL_COLOR);

	utils::DrawRect(m_Collider);

	m_Spritesheet->Draw();
}

void Player::Update(float elapsedSec)
{
	m_ElapsedSec = elapsedSec;


	//Wall sliding
	if (m_PlayerState == PlayerState::wallSlide)
	{
		m_Velocity.x = 0.f;
		m_Velocity.y = -10.f;
	}
	MoveInput(elapsedSec);
	ChangeStates();

	//Temorary code for testing
	if(m_PlayerState != PlayerState::wallSlide)
	{
		m_Velocity.y -= GRAVITY.y * elapsedSec;
	}

	//Half working collisions, gotta fix them
	HandlePlatformCollision(elapsedSec, Level::m_PlatformsArr);
	HandleCollision(elapsedSec, Level::m_ColliderArr);

	if (m_PlayerState != PlayerState::dash)
	{
		m_Position += m_Velocity * elapsedSec;
	}
	
	m_Collider.left = m_Position.x - m_Collider.width / 2;
	m_Collider.bottom = m_Position.y - (m_Collider.height / 2 + 7.f);
	

	//Setting the player animation based on velocity
	ChangeAnimation();
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

void Player::MoveInput(float& elapsedSec)
{
	m_Velocity.x = 0.f;

	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	if (pStates[SDL_SCANCODE_A])
	{
		m_isFlipped = true;
		m_Velocity.x = -SPEED;
		m_PlayerState = PlayerState::walking;
	}
	if (pStates[SDL_SCANCODE_D])
	{
		m_isFlipped = false;
		m_Velocity.x = SPEED;
		m_PlayerState = PlayerState::walking;
	}
	if (pStates[SDL_SCANCODE_SPACE])
	{
		if (m_isOnGround)
		{
			m_Velocity.y = JUMP_PWR;
			m_PlayerState = PlayerState::jump;
			m_isOnGround = false;
		}
		//if (m_isOnGround)
		//{
		//	m_Velocity.y = JUMP_PWR * 2;
		//	m_PlayerState = PlayerState::jump;
		//	m_isOnGround = false;
		//}
		//else if (!m_isOnGround && m_PlayerState == PlayerState::wallSlide)
		//{
		//	m_Velocity.y = JUMP_PWR;
		//	m_Velocity.x = m_isFlipped ? 1000.f : -1000.f;
		//
		//	m_isFlipped = !m_isFlipped;
		//	m_PlayerState = PlayerState::jump;
		//	m_isOnGround = false;
		//}
	}
}

void Player::ChangeStates()
{
	if (m_PlayerState != PlayerState::dash)
	{
		if (m_PlayerState != PlayerState::wallSlide)
		{
			if (m_PlayerState != PlayerState::attack)
			{
				if (!m_isOnGround)
				{
					m_PlayerState = m_Velocity.y > 0.f ? PlayerState::jump : PlayerState::fall;
				}
				if (m_isOnGround)
				{
					m_PlayerState = m_Velocity.x == 0.f ? PlayerState::idle : PlayerState::walking;
				}
			}
		}
		if (m_WallHit && !m_isOnGround)
		{
			m_PlayerState = PlayerState::wallSlide;
		}
	}

	//End the attack animation
	if (m_Spritesheet->GetColIdx() == 4 && m_PlayerState == PlayerState::attack)
	{
		m_PlayerState = PlayerState::idle;
	}
}
void Player::Dash(const SDL_KeyboardEvent& e)
{
	if (e.keysym.sym == SDLK_LSHIFT)
	{
		if (!m_isFlipped)
			m_Position.x += 200.f;
		else
			m_Position.x -= 200.f;
	}
}

void Player::Attack(const SDL_MouseButtonEvent& e)
{
	if (e.button==SDL_BUTTON_LEFT)
	{
		m_Spritesheet->ResetAnim();
		m_PlayerState = PlayerState::attack;
	}
}

void Player::HandleCollision(float elapsedSec, const std::vector<std::vector<Point2f>>& polysVector)
{
	const Vector2f nextPos{ m_Position.x + m_Velocity.x * elapsedSec,
								m_Position.y + m_Velocity.y * elapsedSec };

	const Rectf nextCollider{ m_Collider.left + m_Velocity.x * elapsedSec,
							  m_Collider.bottom + m_Velocity.y * elapsedSec,
							  m_Collider.width,
							  m_Collider.height };



	//Points from player
	const Point2f midRight{ m_Collider.left + m_Collider.width, m_Collider.bottom + m_Collider.height / 2};
	const Point2f midLeft	{ m_Collider.left, m_Collider.bottom + m_Collider.height / 2 };

	const Point2f bottomLeft	{ m_Collider.left, m_Collider.bottom };
	const Point2f topLeft		{ m_Collider.left, m_Collider.bottom + m_Collider.height };
	const Point2f topRight		{ m_Collider.left + m_Collider.width, m_Collider.bottom + m_Collider.height };
	const Point2f bottomRight	{ m_Collider.left + m_Collider.width, m_Collider.bottom };

	//Next points from player
	const Point2f nextMidLeft	{ nextCollider.left, nextCollider.bottom + nextCollider.height/2 };
	const Point2f nextMidRight{  nextCollider.left + nextCollider.width, nextCollider.bottom + nextCollider.height / 2 };

	const Point2f nextBottomLeft	{ nextCollider.left, nextCollider.bottom };
	const Point2f nextTopLeft		{ nextCollider.left, nextCollider.bottom + nextCollider.height };
	const Point2f nextTopRight		{ nextCollider.left + nextCollider.width, nextCollider.bottom + nextCollider.height };
	const Point2f nextBottomRight	{ nextCollider.left + nextCollider.width, nextCollider.bottom };

	utils::HitInfo infoMidLeft{};
	utils::HitInfo infoMidRight{};

	utils::HitInfo infoBottomLeft{};
	utils::HitInfo infoBottomRight{};
	utils::HitInfo infoTopLeft{};
	utils::HitInfo infoTopRight{};



	// Check collision with the world
	for (const auto& poly : polysVector)
	{
		const bool hitMidLeft{ Raycast(poly, midLeft, nextMidLeft, infoMidLeft) };
		const bool hitMidRight{ Raycast(poly,midRight, nextMidRight, infoMidRight) };

		const bool hitBottomLeft{ Raycast(poly, bottomLeft, nextBottomLeft, infoBottomLeft) };
		const bool hitBottomRight{ Raycast(poly, bottomRight, nextBottomRight, infoBottomRight) };
		const bool hitTopLeft{ Raycast(poly, topLeft, nextTopLeft, infoTopLeft) };
		const bool hitTopRight{ Raycast(poly, topRight, nextTopRight, infoTopRight) };


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
		if (hitMidLeft)
		{
			avgNormal += infoBottomLeft.normal;
			avgLambda += infoBottomLeft.lambda;
			++avgCount;
		}

		if (hitMidRight)
		{
			avgNormal += infoBottomRight.normal;
			avgLambda += infoBottomRight.lambda;
			++avgCount;
		}
		if (avgCount != 0.f)
		{
			avgNormal /= avgCount;
			avgLambda /= avgCount;
		}

		m_isOnGround = false;

		m_isOnGround = infoBottomLeft.normal.y > 0.f || infoBottomRight.normal.y > 0.f;

		if (infoTopLeft.normal.y < 0.f || infoTopRight.normal.y < 0.f)
		{
			m_Velocity.y = 0.f;
		}
		
		if (m_isOnPlatform)
		{
			m_isOnGround = true;
		}

		if (infoMidLeft.normal.x > 0.f)
		{
			m_WallHit = true;
		}
		else if (infoMidRight.normal.x < 0.f)
		{
			m_WallHit = true;
		}
		else
		{
			m_WallHit = false;
		}
		if (!m_isOnGround && ((infoBottomLeft.normal.x > 0.f || infoBottomRight.normal.x < 0.f) || 
							  (infoTopLeft.normal.x > 0.f || infoTopRight.normal.x < 0.f)))
		{
			m_WallHit = true;
		}

		if (m_isOnGround)
		{
			m_Velocity.y = 0.f;
		}
		if (m_WallHit)
		{
			m_Velocity.x = 0.f;
		}
	}
}

void Player::HandlePlatformCollision(float elapsedSec, const std::vector<Platform*>& platformVector)
{
	const Vector2f nextPos{ m_Position.x + m_Velocity.x * elapsedSec,
								m_Position.y + m_Velocity.y * elapsedSec };

	const Rectf nextCollider{ m_Collider.left + m_Velocity.x * elapsedSec,
							  m_Collider.bottom + m_Velocity.y * elapsedSec,
							  m_Collider.width,
							  m_Collider.height };



	//Points from player
	const Point2f midRight{ m_Collider.left + m_Collider.width, m_Collider.bottom + m_Collider.height / 2 };
	const Point2f midLeft{ m_Collider.left, m_Collider.bottom + m_Collider.height / 2 };

	const Point2f bottomLeft{ m_Collider.left, m_Collider.bottom };
	const Point2f topLeft{ m_Collider.left, m_Collider.bottom + m_Collider.height };
	const Point2f topRight{ m_Collider.left + m_Collider.width, m_Collider.bottom + m_Collider.height };
	const Point2f bottomRight{ m_Collider.left + m_Collider.width, m_Collider.bottom };

	//Next points from player
	const Point2f nextMidLeft{ nextCollider.left, nextCollider.bottom + nextCollider.height / 2 };
	const Point2f nextMidRight{ nextCollider.left + nextCollider.width, nextCollider.bottom + nextCollider.height / 2 };

	const Point2f nextBottomLeft{ nextCollider.left, nextCollider.bottom };
	const Point2f nextTopLeft{ nextCollider.left, nextCollider.bottom + nextCollider.height };
	const Point2f nextTopRight{ nextCollider.left + nextCollider.width, nextCollider.bottom + nextCollider.height };
	const Point2f nextBottomRight{ nextCollider.left + nextCollider.width, nextCollider.bottom };

	utils::HitInfo infoMidLeft{};
	utils::HitInfo infoMidRight{};

	utils::HitInfo infoBottomLeft{};
	utils::HitInfo infoBottomRight{};
	utils::HitInfo infoTopLeft{};
	utils::HitInfo infoTopRight{};

	for (Platform* platform : platformVector)
	{
		const Point2f bottomLeftC	{ platform->GetCollider().left, platform->GetCollider().bottom};
		const Point2f topLeftC		{ platform->GetCollider().left, platform->GetCollider().bottom + platform->GetCollider().height };
		const Point2f topRightC		{ platform->GetCollider().left + platform->GetCollider().width, platform->GetCollider().bottom + platform->GetCollider().height };
		const Point2f bottomRightC	{ platform->GetCollider().left + platform->GetCollider().width, platform->GetCollider().bottom };

		const std::vector<Point2f> poly = { bottomLeftC,topLeftC,topRightC,bottomRightC};

		// Check collision with the COLLIDERS (platforms)
		const bool hitMidLeft{ Raycast(poly, midLeft, nextMidLeft, infoMidLeft) };
		const bool hitMidRight{ Raycast(poly,midRight, nextMidRight, infoMidRight) };

		const bool hitBottomLeft{ Raycast(poly, bottomLeft, nextBottomLeft, infoBottomLeft) };
		const bool hitBottomRight{ Raycast(poly, bottomRight, nextBottomRight, infoBottomRight) };
		const bool hitTopLeft{ Raycast(poly, topLeft, nextTopLeft, infoTopLeft) };
		const bool hitTopRight{ Raycast(poly, topRight, nextTopRight, infoTopRight) };


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
		if (hitMidLeft)
		{
			avgNormal += infoBottomLeft.normal;
			avgLambda += infoBottomLeft.lambda;
			++avgCount;
		}

		if (hitMidRight)
		{
			avgNormal += infoBottomRight.normal;
			avgLambda += infoBottomRight.lambda;
			++avgCount;
		}
		if (avgCount != 0.f)
		{
			avgNormal /= avgCount;
			avgLambda /= avgCount;
		}

		MovingPlatform* movPlat = dynamic_cast<MovingPlatform*>(platform);
		FadeOutPlatform* fadePlat = dynamic_cast<FadeOutPlatform*>(platform);
		
		if (movPlat != nullptr)
		{
			m_isOnPlatform = false;
			m_isOnPlatform = infoBottomLeft.normal.y > 0.f || infoBottomRight.normal.y > 0.f;

			if (m_isOnPlatform)
			{
				m_Velocity.y = 0.f;
				m_Velocity.x += movPlat->GetVelocityX();
			}
			if ((utils::IsPointInPolygon(midLeft, poly) || utils::IsPointInPolygon(midRight, poly)) ||
				(utils::IsPointInPolygon(bottomLeft, poly) || utils::IsPointInPolygon(bottomRight, poly) || utils::IsPointInPolygon(topLeft, poly) || utils::IsPointInPolygon(topRight, poly) && !m_isOnPlatform))
			{
				m_Velocity.x = movPlat->GetVelocityX();
			}
		}
		if (fadePlat != nullptr)
		{
			m_isOnPlatform = false;
			m_isOnPlatform = infoBottomLeft.normal.y > 0.f || infoBottomRight.normal.y > 0.f;

			if (m_isOnPlatform)
			{
				fadePlat->SetCollision(true);

				if (!fadePlat->GetIsInteractable())
				{
					m_isOnPlatform = false;
				} 
			}
		}
	}
}

void Player::ChangeAnimation()
{
	m_Spritesheet->SetIsFlipped(m_isFlipped);

	m_Spritesheet->SetAnimation(int(m_PlayerState));

}

int Player::GetNrLives() const
{
	return m_NrLives;
}

Vector2f Player::GetPosition() const
{
	return m_Position;
}

Vector2f Player::GetVelocity() const
{
	return m_Velocity;
}
