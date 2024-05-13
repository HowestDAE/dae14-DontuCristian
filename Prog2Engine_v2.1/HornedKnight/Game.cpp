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
	m_HudPtr = new HUD{};

	m_LevelPtr = new Level{ "Level.svg","Level.png" };
	m_PlayerPtr = new Player{Vector2f{30.f,70.f}, "PlayerSpritesheet.png"};

}

void Game::Cleanup()
{
	delete m_PlayerPtr;
	delete m_LevelPtr;
	//delete TextureManager::GetInstance();
}

void Game::Update( float elapsedSec )
{
	m_LevelPtr->Update(elapsedSec);
	m_PlayerPtr->Update(elapsedSec);
	Camera::GetInstance()->SetTarget(m_PlayerPtr->GetPosition());
	Camera::GetInstance()->Update(elapsedSec,m_LevelPtr->GetScaleFactor());

	if (m_MouseClick)
		ParticleManager::GetInstance()->Emit(elapsedSec, ParticleType::dash, Vector2f{mousePos.x,mousePos.y});

	ParticleManager::GetInstance()->Update(elapsedSec,mousePos.y);
	m_HudPtr->Update(elapsedSec);
}

void Game::Draw() const
{
	const Point2f camPos{ Camera::GetInstance()->GetPosition() };
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
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	m_PlayerPtr->Dash(e);
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
	mousePos.x = e.x;
	mousePos.y = e.y;
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		mousePos.x = float(e.x);
		mousePos.y = float(e.y);
		//Player::SetNrLives(--lives);
		m_MouseClick = true;
		break;
	}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	m_PlayerPtr->Attack(e);

	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		m_MouseClick = false;
		break;
	}
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
