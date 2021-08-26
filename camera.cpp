#include "Camera.h"
#include "Game.h"

extern Game *g_pGame;


//-----------------------------------------------------------------------------
// Construction, destruction
//-----------------------------------------------------------------------------
Camera :: Camera( VECTOR &Pos, float mass ) : Body( Pos, mass )
{
	m_d0 = 5.0f;
	m_inertia = 5.0f;
}

Camera :: ~Camera() {}


//-----------------------------------------------------------------------------
// Properties
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Methods
//-----------------------------------------------------------------------------
void Camera :: update()
{
	Object *pCar = g_pGame->world()->car();

//	VECTOR P0 = pCar->Pos() - 10.0f * pCar->J() +
//							   2.5f * pCar->K();
//	VECTOR P0 = pCar->Pos() - 10.0f * pCar->J();
//	P0.z = 2.5f;

	VECTOR P0( 0.0f, -10.0f, 2.5f );

	addForce( 100.0f * ( P0 - m_Pos ) );
//	addVelo( 0.001f * ( P0 - m_Pos ) );


//	VECTOR L0 = pCar->Pos() + 1.5f * pCar->K();
//	VECTOR L0 = pCar->Pos();
//	L0.z = 1.5f;
	VECTOR L0( 0.0f, 0.0f, 1.0f );

	VECTOR D = L0 - m_Pos;
//	VECTOR D = L0 - P0;
	float  d = D3DXVec3Length( &D );
	D3DXVec3Normalize( &D, &D );

	VECTOR J_cam = J();

	if( D3DXVec3Dot( &J_cam, &D ) < 1.0f )
	{
		VECTOR W;
		D3DXVec3Cross( &W, &J_cam, &D );
		addTorque( 100.0f * W );
	}


	VECTOR Z_world = VECTOR( 0.0f, 0.0f, 1.0f );
	VECTOR I_cam   = I();
	float f  = D3DXVec3Dot( &I_cam, &Z_world );
	addTorque( 25.0f * f * J() );


	addForce  ( -100.0f * m_Velo );
	addTorque ( -100.0f * m_Omega );

//	Body :: update();
}
