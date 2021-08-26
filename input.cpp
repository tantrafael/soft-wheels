#include "Input.h"
#include "Game.h"

extern Game *g_pGame;


Input::Input()
{
	m_pDI       = NULL;
	m_pKeyboard = NULL;
	m_pMouse    = NULL;

	m_InitDI();
}

Input::~Input()
{
	m_TermDI();
}


//-----------------------------------------------------------------------------
// Name: read()
// Desc:
//-----------------------------------------------------------------------------
void Input::read()
{
	World  *pWorld  = g_pGame->world();
	Camera *pCamera = g_pGame->world()->camera();
	Car    *pCar    = g_pGame->world()->car();
	Object *pWheel  = g_pGame->world()->m_pWheel;
	Object *pBall   = g_pGame->world()->m_pBall;
	Object *pBody   = g_pGame->world()->m_pBody;


/*
	// Mouse
	DIMOUSESTATE dims;
	m_pMouse->GetDeviceState( sizeof( DIMOUSESTATE ), &dims );

	float dx = 0.001f * dims.lX;
	float dy = 0.001f * dims.lY;
	pCamera->addTorque( -dx * VECTOR( 0.0f, 0.0f, 1.0f ) );
	pCamera->addTorque( -dy * pCamera->I() );
*/

	// Keyboard
	#define KEYDOWN( name, key ) ( name[key] & 0x80 )
	char buffer[256];
	m_pKeyboard->GetDeviceState( sizeof(buffer), (LPVOID)&buffer );

	if( KEYDOWN( buffer, DIK_W ) ) { pCar->forward(); }
	if( KEYDOWN( buffer, DIK_S ) ) { pCar->back();    }
	if( KEYDOWN( buffer, DIK_A ) ) { pCar->left();    }
	if( KEYDOWN( buffer, DIK_D ) ) { pCar->right();   }

//	if( KEYDOWN( buffer, DIK_W ) ) { pWheel->addTorque (-0.1f * pWheel->I() ); }
//	if( KEYDOWN( buffer, DIK_S ) ) { pWheel->addTorque ( 0.1f * pWheel->I() ); }
//	if( KEYDOWN( buffer, DIK_E ) ) { pWheel->addForce  ( VECTOR( 0, 0.2f, 0 ) ); }
//	if( KEYDOWN( buffer, DIK_D ) ) { pWheel->addForce  ( VECTOR( 0,-0.2f, 0 ) ); }

//	if( KEYDOWN( buffer, DIK_W ) ) { pBall->addTorque (-0.1f * pBall->I() ); }
//	if( KEYDOWN( buffer, DIK_S ) ) { pBall->addTorque ( 0.1f * pBall->I() ); }
//	if( KEYDOWN( buffer, DIK_E ) ) { pBall->addForce  ( VECTOR( 0, 0.2f, 0 ) ); }
//	if( KEYDOWN( buffer, DIK_D ) ) { pBall->addForce  ( VECTOR( 0,-0.2f, 0 ) ); }

//	if( KEYDOWN( buffer, DIK_W ) ) { pBody->addTorque (-0.1f * pBody->I() ); }
//	if( KEYDOWN( buffer, DIK_S ) ) { pBody->addTorque ( 0.1f * pBody->I() ); }
//	if( KEYDOWN( buffer, DIK_E ) ) { pBody->addForce  ( VECTOR( 0, 0.2f, 0 ) ); }
//	if( KEYDOWN( buffer, DIK_D ) ) { pBody->addForce  ( VECTOR( 0,-0.2f, 0 ) ); }

/*
	if( KEYDOWN( buffer, DIK_UP ) )
	{
		pCamera->addForce(  0.1f * pCamera->J() );
	}

	if( KEYDOWN( buffer, DIK_DOWN ) )
	{
		pCamera->addForce( -0.1f * pCamera->J() );
	}
*/

/*
	if( KEYDOWN( buffer, DIK_LEFT ) )
	{
		pCamera->addTorque( 0.01f * pCamera->k() );
	}

	if( KEYDOWN( buffer, DIK_RIGHT ) )
	{
		pCamera->addTorque( -0.01f * pCamera->k() );
	}
*/

//	Car *g_pPlayerCar = g_pGame->world()->PlayerCar();
//	if( KEYDOWN( buffer, DIK_UP    ) ) { g_pPlayerCar->gas   (); }
//	if( KEYDOWN( buffer, DIK_DOWN  ) ) { g_pPlayerCar->brake (); }
//	if( KEYDOWN( buffer, DIK_LEFT  ) ) { g_pPlayerCar->left  (); }
//	if( KEYDOWN( buffer, DIK_RIGHT ) ) { g_pPlayerCar->right (); }
}


//-----------------------------------------------------------------------------
// Name: m_InitDI()
// Desc:
//-----------------------------------------------------------------------------
HRESULT Input::m_InitDI()
{
	HRESULT hr;

	HINSTANCE hInst = g_pGame->window()->hInst ();
	HWND      hWnd  = g_pGame->window()->hWnd  ();

	// Create DirectInput object
	hr = DirectInput8Create( hInst,
							 DIRECTINPUT_VERSION,
							 IID_IDirectInput8,
							 (void**) &m_pDI,
							 NULL );

	// Mouse
	m_pDI->CreateDevice( GUID_SysMouse, &m_pMouse, NULL );
	m_pMouse->SetDataFormat( &c_dfDIMouse );
	m_pMouse->SetCooperativeLevel( hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
	HANDLE hMouseEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_pMouse->SetEventNotification( hMouseEvent );
	m_pMouse->Acquire();

	// Keyboard
	m_pDI->CreateDevice( GUID_SysKeyboard, &m_pKeyboard, NULL );
	m_pKeyboard->SetDataFormat( &c_dfDIKeyboard );
	m_pKeyboard->SetCooperativeLevel( hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
	m_pKeyboard->Acquire();

	return S_OK;
}


//-----------------------------------------------------------------------------
// Name: m_TermDI()
// Desc:
//-----------------------------------------------------------------------------
void WINAPI Input::m_TermDI()
{
	if( m_pDI )
	{
		if( m_pKeyboard )
		{
			m_pKeyboard->Release();
			m_pKeyboard = NULL;
		}
		m_pDI->Release();
		m_pDI = NULL;
	}
}
