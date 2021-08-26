#ifndef __INPUT_H__
#define __INPUT_H__

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

#pragma comment ( lib, "dinput8.lib" )
#pragma comment ( lib, "dxguid.lib" )

#include "definitions.h"


class Input
{
	public:
		Input();
	   ~Input();

		void read();

	protected:
		LPDIRECTINPUT8       m_pDI;
		LPDIRECTINPUTDEVICE8 m_pKeyboard;
		LPDIRECTINPUTDEVICE8 m_pMouse;

		HRESULT m_InitDI();
		void WINAPI m_TermDI();
};

#endif