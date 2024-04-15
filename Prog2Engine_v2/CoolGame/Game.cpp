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
	m_LevelPtr = new Level{ "Level.svg","Level.png" };
	m_PlayerPtr = new Player{Point2f{20,40},90.f,250.f, "Player_8x5.png"};
}

void Game::Cleanup( )
{
	delete m_PlayerPtr;
	delete m_LevelPtr;
}

void Game::Update( float elapsedSec )
{
	//rect = Rectf{ mousePos.x,mousePos.y,20,20 };
	m_PlayerPtr->Update(elapsedSec);
	Camera::GetInstance()->SetTarget(m_PlayerPtr->GetPosition());
	Camera::GetInstance()->Update(elapsedSec,m_LevelPtr->m_ScaleFactor);
}

void Game::Draw( ) const
{
	const Point2f camPos{ Camera::GetInstance()->GetPosition() };
	ClearBackground(Color4f{ 0.f,0.f,0.f,1.f });
	glPushMatrix();
	{
		glTranslatef(-camPos.x, -camPos.y, 0.f);
		glScalef(m_LevelPtr->m_ScaleFactor, m_LevelPtr->m_ScaleFactor, 1.f);
		m_LevelPtr->Draw();
		m_PlayerPtr->Draw();
	}glPopMatrix();

	utils::SetColor(Color4f{0,1,0,1});
	
	
	//TestCode

	//int mr{ 3 };
	//
	//if (int(Collisions::IsRectInPoly(rect, Level::m_Collider)) == 2||
	//	int(Collisions::IsRectInPoly(rect, Level::m_Collider)) == 3
	//	)
	//{
	//	utils::SetColor(Color4f{ 1, 0, 0, 1 });
	//	utils::FillRect(rect);
	//}
	//else
	//{
	//	utils::SetColor(Color4f{ 1, 1, 1, 1 });
	//	utils::FillRect(rect);
	//}
	//for (int idx{}; idx < mr; idx++)
	//{
	//	//raycasts to the bottom
	//	Point2f r1P1{ rect.left + idx * rect.width / (mr - 1),rect.bottom + rect.height / 2 };
	//	Point2f r1P2{ rect.left + idx * rect.width / (mr - 1),rect.bottom };
	//
	//	//raycasts to the top
	//	Point2f r2P1{ rect.left + idx * rect.width / (mr - 1),rect.bottom + rect.height / 2 };
	//	Point2f r2P2{ rect.left + idx * rect.width / (mr - 1),rect.bottom + rect.height };
	//
	//	//raycasts to the left
	//	Point2f r3P1{ rect.left + rect.width / 2,rect.bottom + idx * rect.height / (mr - 1) };
	//	Point2f r3P2{ rect.left					,rect.bottom + idx * rect.height / (mr - 1) };
	//
	//	//raycasts to the right
	//	Point2f r4P1{ rect.left + rect.width / 2,rect.bottom + idx * rect.height / (mr - 1) };
	//	Point2f r4P2{ rect.left + rect.width,	 rect.bottom + idx * rect.height / (mr - 1) };
	//
	//	utils::SetColor(Color4f{ 0,1,0,1 });
	//	utils::DrawLine(r1P1, r1P2);
	//	utils::DrawLine(r2P1, r2P2);
	//	utils::DrawLine(r3P1, r3P2);
	//	utils::DrawLine(r4P1, r4P2);
	//}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	m_PlayerPtr->Jump(e);
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
	//mousePos.x = e.x;
	//mousePos.y = e.y;
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{

	//std::cout << "MOUSEBUTTONDOWN event: ";
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

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
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
