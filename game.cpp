#include "Game.h"

extern Game *g_pGame;


Game::Game( HINSTANCE hInst, HWND hWnd, int width, int height )
{
	g_pGame     = this;
	m_pWindow   = new Window( hInst, hWnd, width, height );
	m_pGraphics = new Graphics();
	m_pInput    = new Input();
	m_pWorld    = new World();
}

Game::~Game()
{
	delete m_pWorld;
	delete m_pInput;
	delete m_pGraphics;
	delete m_pWindow;
}


Window*	  Game::window()   { return m_pWindow;   }
Graphics* Game::graphics() { return m_pGraphics; }
Input*	  Game::input()	   { return m_pInput;    }
World*	  Game::world()	   { return m_pWorld;    }


void Game::update()
{
	m_pInput->read();
	m_pWorld->update();
	m_pWorld->render();
}
