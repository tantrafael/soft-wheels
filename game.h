#ifndef __GAME_H__
#define __GAME_H__

#include "definitions.h"
#include "Window.h"
#include "World.h"
#include "Graphics.h"
#include "Input.h"

class Game
{
	public:
		Game( HINSTANCE hInst, HWND hWnd, int width, int height );
	   ~Game();

		Window*	  window();
		World*	  world();
		Graphics* graphics();
		Input*	  input();

		void update();

	protected:
		Window   *m_pWindow;
		World	 *m_pWorld;
		Graphics *m_pGraphics;
		Input	 *m_pInput;
};

#endif