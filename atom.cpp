#include "Atom.h"
#include "Game.h"

extern Game *g_pGame;


//--------------------------------------------------------------------
// Construction, destruction
//--------------------------------------------------------------------
Atom :: Atom( VECTOR &pos, float mass ) : Mass( pos, mass )
//Atom :: Atom( VECTOR &pos, float mass ) : Body( pos, mass )
{
//	g_pGame->world()->addAtom( this );
//	m_k = 5.0f;

	float r   = 0.1f;
//	m_inertia = 0.4f * m_mass * r * r;
	m_inertia = 1.0f;
}

Atom :: ~Atom() {}


//--------------------------------------------------------------------
// Properties
//--------------------------------------------------------------------
float Atom :: inertia( VECTOR &A )
{
	return m_inertia;
}


//--------------------------------------------------------------------
VECTOR Atom :: Force()
{
	VECTOR F(0,0,0);

	// Gravitational force
	VECTOR F_gravity = m_mass * g_pGame->world()->gravity();

	F += F_gravity;

	if( m_Pos.z < 0.0f )
	{
		VECTOR N = VECTOR( 0.0f, 0.0f, 1.0f );

		// Normal force
		float d = m_k * ( 0.0f - m_Pos.z );
		VECTOR F_normal = d * N;

		F += F_normal;

	/*
		// Friction
		VECTOR D = m_Pos_1 - m_Pos;
		D.z = 0;
		VECTOR F_friction = 0.25f * D;

		F += F_friction;
	*/

	}

	for( int i = 0; i < m_nrBindings; ++i )
	{
		VECTOR F_binding_i = m_ppBindings[ i ]->Force( this );
		F += F_binding_i;
	}

	return F;
}

//--------------------------------------------------------------------
VECTOR Atom :: MostCollidedPoint()
{
	return m_Pos;
}

//--------------------------------------------------------------------
// Methods
//--------------------------------------------------------------------
void Atom :: update()
{
	VECTOR mG = m_mass * g_pGame->world()->gravity();
	addForce( mG );

	//----------------------------------------------------------------
	Mass :: update();

	//----------------------------------------------------------------
	if( m_Pos.z < 0.0f )
	{
		float  v = D3DXVec3Length( &m_Velo );
		VECTOR N = VECTOR( 0.0f, 0.0f, 1.0f );

		VECTOR D1, D2;
		VECTOR dP = m_Pos - m_Pos_1;
		D3DXVec3Normalize( &D1, &dP );
		D2 = D1 - 2.0f * D3DXVec3Dot( &D1, &N ) * N;

		float  dp   = D3DXVec3Length( &dP );
		float  dp_N = dP.z;
		float  e_N  = m_Pos.z - 0.0f;
		float  e    = e_N * dp / dp_N;
		float  s    = dp - e;

		VECTOR P0 = m_Pos_1 + s * D1;
		VECTOR P1 =   P0    + e * D2;

	//	m_Pos  = P1;
		m_Pos  = P0;
		m_Velo = m_Velo - 1.9f * D3DXVec3Dot( &m_Velo, &N ) * N;

		float k = 1.0f - 1.0f / ( v + 1.0f );
		m_Velo  = k * m_Velo;
	}

//	m_Velo = 0.90f * m_Velo;
}


//--------------------------------------------------------------------
void Atom :: render()
{
	g_pGame->graphics()->Point( m_Pos );
}