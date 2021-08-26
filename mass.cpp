#include "Mass.h"
#include "Game.h"

extern Game *g_pGame;


//------------------------------------------------------------
// Construction, destruction
//------------------------------------------------------------
Mass :: Mass()
{
	init();
}


Mass :: Mass( VECTOR &Pos, float mass )
{
	init();

	m_mass  = mass;
	m_Pos   = Pos;
	m_Pos_1 = Pos;
}

Mass :: ~Mass() {}


//------------------------------------------------------------
// Properties
//------------------------------------------------------------
float  Mass :: mass    () { return m_mass;  }
VECTOR Mass :: Pos     () { return m_Pos;   }
VECTOR Mass :: Pos_1   () { return m_Pos_1; }
VECTOR Mass :: Force   () { return m_Force; }
VECTOR Mass :: Velo    () { return m_Velo;  }

float  Mass :: inertia( VECTOR &A, VECTOR &P )
{
	VECTOR R = m_Pos - P;
	VECTOR RxA;
	D3DXVec3Cross( &RxA, &R, &A );

	float d2 = D3DXVec3LengthSq( &RxA ) /
			   D3DXVec3LengthSq( &A );

	return m_mass * d2;
}


//------------------------------------------------------------
// Methods
//------------------------------------------------------------
void Mass :: init()
{
	m_mass  = 0.0f;
	m_Force = VECTOR(0,0,0);
	m_Pos   = m_Pos_1 = VECTOR(0,0,0);
	m_Acc   = VECTOR(0,0,0);
	m_Velo  = VECTOR(0,0,0);
	m_t     = m_t_1 = 0.001f * GetTickCount();
}


//------------------------------------------------------------
void Mass :: setMass  ( float   m ) { m_mass   = m; }
void Mass :: setPos   ( VECTOR &P ) { m_Pos    = P; }
void Mass :: setPos_1 ( VECTOR &P ) { m_Pos_1  = P; }
void Mass :: setVelo  ( VECTOR &V ) { m_Velo   = V; }
void Mass :: setForce ( VECTOR &F ) { m_Force  = F; }
void Mass :: addVelo  ( VECTOR &V ) { m_Velo  += V; }
void Mass :: addForce ( VECTOR &F ) { m_Force += F; }


//------------------------------------------------------------
void Mass :: move( VECTOR &V )
{
	m_Pos_1 = m_Pos;
	m_Pos += V;
}


//------------------------------------------------------------
void Mass :: rotate( VECTOR &W, VECTOR &P )
{
	MATRIX R;
	D3DXMatrixRotationAxis( &R, &W, D3DXVec3Length( &W ) );

	VECTOR D = m_Pos - P;
	VECTOR D1;
	D3DXVec3TransformCoord( &D1, &D, &R );

	m_Pos = P + D1;
//	setPos( P + D1 );
}


//------------------------------------------------------------
void Mass :: update_trans()
{
	float dt  = g_pGame->world()->dt();
//	float dt  = 0.025f;
//	float dt2 = g_pGame->world()->dt2();
//	float timeconst = g_pGame->world()->timeconst();

/*
	move( m_Velo * dt );

	m_Velo = m_Velo + m_Acc * dt;

	m_Acc  = m_Force / m_mass;
*/


	m_Acc  = m_Force / m_mass;

	m_Velo = m_Velo + m_Acc * dt;

	move( m_Velo * dt );


	m_Force = VECTOR(0,0,0);
}


//------------------------------------------------------------
void Mass :: update()
{
	update_trans();
}
