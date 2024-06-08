#pragma once
#include "BaseGame.h"
#include "SoundStream.h"
#include "StringSprite.h"
#include "Player.h"
#include "Level.h"
#include "Camera.h"
#include "ParticleManager.h"
#include "Platform.h"
#include "MovingPlatform.h"
#include "HUD.h"
#include "BulletEmitter.h"

enum class GameState
{
	intro,
	running,
	outro
};

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground(Color4f bg = Color4f{0.3f,0.0f,0.8f,1.f}) const;

	// Member variables
	GameState m_GameState{GameState::intro};
	SoundStream* m_BackgroundMusic{};

	Player* m_PlayerPtr{};
	Level*	m_LevelPtr{};
	HUD*	m_HudPtr{};

	Sprite* m_MenuBackground{};
	StringSprite* m_MenuText{};

	bool m_MouseClick{false};
	int lives{ 6 };

	bool m_EmitParticles{false};
};