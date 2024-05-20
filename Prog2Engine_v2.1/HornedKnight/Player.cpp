#include "pch.h"
#include "Player.h"

int Player::m_NrLives = { 6 };

Player::Player(const Vector2f& pos, const std::string& filePath,
	int rows, int columns, float frameDelay):
	m_isAlive			{true},
	m_Velocity			{0.f,0.f},
	m_isOnGround		{false},
	m_isOnPlatform		{false},
	m_isFlipped			{false},
	m_PlayerState		{PlayerState::idle},
	m_WallHit			{false},
	m_InputNorm			{1.f,0.f}
{
	m_Position = pos;
	m_AttackRange = Circlef{ Point2f{pos.x + 5.f,pos.y - 5.f}, 10};
	m_Spritesheet = new Sprite{ filePath,pos, rows, columns, frameDelay };
	m_Collider = Rectf{ pos.x-5.f , pos.y-16.f,10.f, 16.f };
}

Player::~Player()
{
	delete m_Spritesheet;
	m_Spritesheet = nullptr;
}

void Player::Draw() const
{
	utils::SetColor(COL_COLOR);

	utils::DrawRect(m_Collider);
	utils::DrawEllipse(m_AttackRange.center,m_AttackRange.radius,m_AttackRange.radius);

	m_Spritesheet->Draw();
}

void Player::Update(float elapsedSec)
{
	m_ElapsedSec = elapsedSec;

	ChangeStates();
	MoveInput(elapsedSec);
	//Wall sliding
	if (m_PlayerState == PlayerState::wallSlide)
	{
		m_Velocity.x = 0.f;
		m_Velocity.y = -30.f;
	}

	//Applying gravity 
	if(m_PlayerState != PlayerState::wallSlide &&
		m_PlayerState != PlayerState::dash)
	{
		m_Velocity.y -= GRAVITY.y * elapsedSec;
	}

	//Fully Working Collisions
	HandleCollision(elapsedSec, Level::m_ColliderArr);
	HandleCollision(elapsedSec, Level::m_PlatformsArr);
	HandleCollision(elapsedSec, Level::m_EnemiesArr);
	HandleCollision(elapsedSec, Level::m_DMGZoneArr);

	m_Position += m_Velocity * elapsedSec;
	
	m_Collider.left = m_Position.x - m_Collider.width / 2;
	m_Collider.bottom = m_Position.y - (m_Collider.height / 2 + 8.f);

	if (m_isFlipped == false)
	{
		m_AttackRange.center.x = m_Position.x + 5.f;
	}
	else if (m_isFlipped == true)
	{
		m_AttackRange.center.x = m_Position.x - 5.f;
	}
	m_AttackRange.center.y = m_Position.y - 5.f;
	
	//Setting the player animation based on velocity
	ChangeAnimation();
	m_Spritesheet->Update(elapsedSec, m_Position);
}

void Player::SetIsAlive(bool myBool)
{
	m_isAlive = myBool;
}

void Player::MoveInput(float& elapsedSec)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	
	if (pStates[SDL_SCANCODE_A])
	{
		//The if stops the player from getting a boost in velocity
		// when you're holding down the movement keys while dashing
		if (m_PlayerState != PlayerState::dash)
		{
			if (m_PlayerState != PlayerState::wallJump)
			{
				m_isFlipped = true;
				m_Velocity.x = -SPEED;
			}
		}

		m_InputNorm.x = -1;

		if (pStates[SDL_SCANCODE_W])
		{
			m_InputNorm.y = 1;
		}
		else
		{
			m_InputNorm.y = 0;
		}
	}
	else if (pStates[SDL_SCANCODE_D])
	{
		//The if stops the player from getting a boost in velocity
		// when you're holding down the movement keys while dashing
		if (m_PlayerState != PlayerState::dash)
		{
			if (m_PlayerState != PlayerState::wallJump)
			{
				m_isFlipped = false;
				m_Velocity.x = SPEED;
			}
		}

		m_InputNorm.x = 1;

		if (pStates[SDL_SCANCODE_W])
		{
			m_InputNorm.y = 1;
		}
		else
		{
			m_InputNorm.y = 0;
		}
	}
	else
	{
		if (m_PlayerState != PlayerState::dash)
		{
			if (m_PlayerState != PlayerState::jump)
			{
				m_Velocity.x = 0.f;
			}
		}
	}
	if (pStates[SDL_SCANCODE_SPACE])
	{
		if (m_isOnGround)
		{
			ParticleManager::GetInstance()->Emit(elapsedSec, ParticleType::dust, Vector2f{ m_Collider.left + m_Collider.width / 2,m_Collider.bottom });

			m_Velocity.y = JUMP_PWR;
			m_PlayerState = PlayerState::jump;
			m_isOnGround = false;
		}
		if (!m_isOnGround && m_PlayerState == PlayerState::wallSlide)
		{
			m_Velocity.y = JUMP_PWR;
			m_Velocity.x = m_isFlipped ? SPEED : -SPEED;
			m_isFlipped = !m_isFlipped;
			m_PlayerState = PlayerState::wallJump;
			m_isOnGround = false;
			ParticleManager::GetInstance()->Emit(elapsedSec, ParticleType::dust, Vector2f{ m_Collider.left + m_Collider.width,m_Collider.bottom + m_Collider.height / 2 });
		}

	}
}

void Player::ChangeStates()
{
	if (m_PlayerState != PlayerState::dash)
	{
		if (m_PlayerState != PlayerState::attack)
		{
			//WallSlide state
			if (m_WallHit && !m_isOnGround)
			{
				m_PlayerState = PlayerState::wallSlide;
			}

			//If it's not wallslide manage the other states
			if (m_PlayerState != PlayerState::wallSlide)
			{
				if (!m_isOnGround)
				{
					if (m_Velocity.y < 0.f)
					{
						m_PlayerState = PlayerState::fall;
					}
				}
				if (m_isOnGround)
				{
					m_PlayerState = m_Velocity.x == 0.f ? PlayerState::idle : PlayerState::walking;
				}
			}
		}
	}
	//End the dash
	if (m_PlayerState == PlayerState::dash)
	{
		m_Dash_AccumulatedTime += m_ElapsedSec;
		if (m_Dash_AccumulatedTime >= DASH_TIME)
		{
			m_PlayerState = PlayerState::idle;
			m_Dash_AccumulatedTime = 0.f;
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
		Vector2f norm = m_InputNorm.Normalized();
		m_PlayerState = PlayerState::dash;
		m_Velocity = m_InputNorm.Normalized() * DASH_SPEED;
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

	const Rectf nextCollider{ m_Collider.left   + m_Velocity.x * elapsedSec,
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

		m_isOnGround = infoBottomLeft.normal.y > 0.f || infoBottomRight.normal.y > 0.f;

		if (infoMidLeft.normal.x > 0.f || infoMidRight.normal.x < 0.f)
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

		//Ground collisions
		if (m_isOnGround)
		{
			m_Velocity.y = 0.f;
		}

		//Ceilling collisions 
		if (infoTopLeft.normal.y < 0.f || infoTopRight.normal.y < 0.f)
		{
			m_Velocity.y = 0.f;
		}

		//Wall collisions
		if (m_WallHit)
		{
			m_Velocity.x = 0.f;
		}
	}
}

void Player::HandleCollision(float elapsedSec, const std::vector<Platform*>& platformVector)
{
	const Rectf nextCollider{ m_Collider.left   + m_Velocity.x * elapsedSec,
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
		const Point2f bottomLeftC{ platform->GetCollider().left, platform->GetCollider().bottom };
		const Point2f topLeftC{ platform->GetCollider().left, platform->GetCollider().bottom + platform->GetCollider().height };
		const Point2f topRightC{ platform->GetCollider().left + platform->GetCollider().width, platform->GetCollider().bottom + platform->GetCollider().height };
		const Point2f bottomRightC{ platform->GetCollider().left + platform->GetCollider().width, platform->GetCollider().bottom };

		const std::vector<Point2f> poly = { bottomLeftC,topLeftC,topRightC,bottomRightC };

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

		m_isOnPlatform = false;

		if (fadePlat != nullptr)
		{
			if (fadePlat->GetIsInteractable())
			{
				m_isOnPlatform = hitBottomLeft || hitBottomRight;
			}
		}

		if (movPlat != nullptr)
		{
			m_isOnPlatform = hitBottomLeft || hitBottomRight;

			if (m_isOnPlatform)
			{
				m_isOnGround = true;
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
			if (m_isOnPlatform)
			{
				m_isOnGround = true;
				m_Velocity.y = 0.f;
				fadePlat->SetCollision(true);
			}
		}
	}
}

void Player::HandleCollision(float elapsedSec,const std::vector<Enemy*>& enemyVector)
{
	bool enemyHit{};
	int currentLives{m_NrLives};
	const float	DMG_COOLDOWN{ 2.f };

	m_DMG_AccumulatedTime += elapsedSec;

	for (Enemy* enemy : enemyVector)
	{
		if (enemy->GetState() != EnemyStates::dead)
		{
			enemyHit = utils::IsOverlapping(m_Collider, enemy->GetCollider());
		
			if (enemyHit)
			{
				currentLives--;
				if (m_DMG_AccumulatedTime >= DMG_COOLDOWN)
				{
					SetNrLives(currentLives);
					ParticleManager::GetInstance()->Emit(elapsedSec, ParticleType::blood, m_Position - Vector2f{ 0.f,6.f });
					

					Camera::GetInstance()->CameraShake();
					m_DMG_AccumulatedTime = 0.f;
				}
				
			}
		}
	}
}

void Player::HandleCollision(float elapsedSec, const std::vector<DMGZone*> dmgZoneVector)
{
	bool zoneHit{};
	int currentLives{ m_NrLives };
	const float	DMG_COOLDOWN{ 2.f };

	m_DMG_AccumulatedTime += elapsedSec;

	for (DMGZone* zone : dmgZoneVector)
	{
		zoneHit = utils::IsOverlapping(m_Collider, zone->GetCollider());

		KillZone* killZone = dynamic_cast<KillZone*>(zone);

		if (killZone != nullptr)
		{
			if (zoneHit)
			{
				currentLives = 0;
				if (m_DMG_AccumulatedTime >= DMG_COOLDOWN)
				{
					SetNrLives(currentLives);
					ParticleManager::GetInstance()->Emit(elapsedSec, ParticleType::blood, m_Position - Vector2f{ 0.f,6.f });

					Camera::GetInstance()->CameraShake();
					m_DMG_AccumulatedTime = 0.f;
				}

			}
		}
		else
		{
			if (zoneHit)
			{
				currentLives--;
				if (m_DMG_AccumulatedTime >= DMG_COOLDOWN)
				{
					SetNrLives(currentLives);
					ParticleManager::GetInstance()->Emit(elapsedSec, ParticleType::blood, m_Position - Vector2f{ 0.f,6.f });

					Camera::GetInstance()->CameraShake();
					m_DMG_AccumulatedTime = 0.f;
				}
			}
		}
	}
}

void Player::ChangeAnimation()
{
	m_Spritesheet->SetIsFlipped(m_isFlipped);

	//the walljump and jump have the same animation
	if (m_PlayerState == PlayerState::wallJump)
	{
		m_Spritesheet->SetAnimation(int(PlayerState::jump));
	}
	m_Spritesheet->SetAnimation(int(m_PlayerState));
}

Vector2f Player::GetPosition() const
{
	return m_Position;
}

Vector2f Player::GetVelocity() const
{
	return m_Velocity;
}

void Player::SetNrLives(int lives)
{
	if(lives >= 0)
		m_NrLives = lives;
}

int Player::GetNrLives()
{
	return m_NrLives;
}
