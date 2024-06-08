#include "pch.h"
#include "Game.h"

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_MenuBackground = new Sprite{ "IntroPage.png",Vector2f{0.f,0.f}};
	m_MenuText = new StringSprite{ "PRESS ENTER TO START","Minecraft.ttf",30,Color4f{1.f,1.f,1.f,1.f},Vector2f{-200.f,0.f}};

	m_BackgroundMusic = new SoundStream{"BackgroundMusic.mp3"};

	m_BackgroundMusic->SetVolume(30);

	m_HudPtr	= new HUD{};
	m_LevelPtr	= new Level{ "Level.svg", "Background.png", "MapPlatforms.png"};
	m_PlayerPtr = new Player{Vector2f{3700.f,40.f}, "PlayerSpritesheet.png"};
}

void Game::Cleanup()
{
	delete m_MenuBackground;
	delete m_MenuText;
	delete m_BackgroundMusic;
	delete m_PlayerPtr;
	delete m_LevelPtr;
	delete m_HudPtr;

	TextureManager::DeleteSingleton();
	Camera::DeleteSingleton();
	ParticleManager::DeleteSingleton();
}

void Game::Update( float elapsedSec )
{
	switch (m_GameState)
	{
	case GameState::intro:
		if (!m_BackgroundMusic->IsPlaying())
		{
			m_BackgroundMusic->Play(false);
		}
		m_MenuText->Recreate("PRESS ENTER TO START");
		break;
	case GameState::running:
		m_LevelPtr->Update(elapsedSec);
		m_PlayerPtr->Update(elapsedSec);
		Camera::GetInstance()->SetTarget(m_PlayerPtr->GetPosition());
		Camera::GetInstance()->Update(elapsedSec, m_LevelPtr->GetScaleFactor());

		ParticleManager::GetInstance()->Update(elapsedSec);
		m_HudPtr->Update(elapsedSec);
		break;
	case GameState::outro:
		m_MenuText->SetPosition(Vector2f{ -150.f,0.f });
		m_MenuText->Recreate("Congratulations!!!");
		break;
	}
}

void Game::Draw() const
{
	const Point2f camPos{ Camera::GetInstance()->GetPosition() };

	switch (m_GameState)
	{
	case GameState::intro:
		glPushMatrix();
		{
			glTranslatef(SCREEN_WIDTH/2.f,SCREEN_HEIGHT/2.f,0.f);
			glScalef(0.625f, 0.625f, 1.f);
			m_MenuBackground->Draw();
			m_MenuText->Draw();
		}glPopMatrix();
		break;
	case GameState::running:
		ClearBackground(Color4f{ 0.f,0.f,0.f,1.f });
		glPushMatrix();
		{
			glTranslatef(-camPos.x, -camPos.y, 0.f);
			glScalef(m_LevelPtr->GetScaleFactor(), m_LevelPtr->GetScaleFactor(), 1.f);
			m_LevelPtr->Draw();
			m_PlayerPtr->Draw();
			ParticleManager::GetInstance()->Draw();
		}glPopMatrix();
		glPushMatrix();
		{
			glScalef(4.5f, 4.5f, 1.f);
			m_HudPtr->Draw();
		}glPopMatrix();
		break;
	case GameState::outro:
		glPushMatrix();
		{
			glTranslatef(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 0.f);
			glScalef(0.625f, 0.625f, 1.f);
			m_MenuBackground->Draw();
			m_MenuText->Draw();
		}glPopMatrix();
		break;
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	if (m_GameState == GameState::running)
	{
		m_PlayerPtr->Dash(e);
		if (e.keysym.sym == SDLK_w)
		{
			if (utils::IsPointInRect(m_PlayerPtr->GetPosition().ToPoint2f(), m_LevelPtr->GetExitDoor()))
			{
				m_GameState = GameState::outro;
			}
		}
	}
	if (m_GameState == GameState::intro)
	{
		if (e.keysym.sym == SDLK_RETURN)
		{
			m_GameState = GameState::running;
		}
	}
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{

	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	if (m_GameState == GameState::running)
	m_PlayerPtr->Attack(e);

	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground(Color4f bg) const
{
	glClearColor(bg.r,bg.g,bg.b,bg.a);
	glClear( GL_COLOR_BUFFER_BIT );
}
