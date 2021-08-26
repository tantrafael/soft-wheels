#include "Ball.h"
#include "Game.h"

extern Game *g_pGame;


//--------------------------------------------------------------------
// Construction, destruction
//--------------------------------------------------------------------
Ball :: Ball( VECTOR &Pos, float mass, float rad ) : Body( Pos, mass )
{
	m_mass = mass;
	m_rad  = rad;
	m_inertia = 1.0f * m_mass * m_rad * m_rad;
}

Ball :: ~Ball() {}


//--------------------------------------------------------------------
// Properties
//--------------------------------------------------------------------
float Ball :: inertia( VECTOR &A )
{
	return m_inertia;
}


//--------------------------------------------------------------------
float Ball :: inertia( VECTOR &A, VECTOR &P )
{
	VECTOR R = m_Pos - P;
	VECTOR RxA;
	D3DXVec3Cross( &RxA, &R, &A );

	float d2 = D3DXVec3LengthSq( &RxA ) /
			   D3DXVec3LengthSq( &A );

	return m_mass * d2;
}


//--------------------------------------------------------------------
// Methods
//--------------------------------------------------------------------
void Ball :: update()
{
	addForce( m_mass * g_pGame->world()->gravity() );

	float d = m_Pos.z - m_rad;

	if( d < 0.0f )
	{
		VECTOR N( 0, 0, 1.0f );
		addForce( -10.0f * d * N );

	/*
		if( D3DXVec3Length( &m_Torque ) > 0.0f )
		{
			VECTOR D;
			VECTOR R = -VECTOR( 0, 0, m_rad );
			D3DXVec3Cross( &D, &m_Torque, &R );
			VECTOR F = -D / ( m_rad * m_rad );

			addForce( F );
		}
	*/

	//	VECTOR V_grad = VECTOR( m_Velo.x, m_Velo.x, 0 );
	//	VECTOR F_friction = -0.1f * V_grad;


	//	m_Pos.z = m_rad;
	//	m_Velo.z = -m_Velo.z;
	}

	Body :: update();


	m_Velo  = 0.95f * m_Velo;
	m_Omega = 0.95f * m_Omega;
}


//--------------------------------------------------------------------
void Ball :: render()
{
	int N_i = 2;
	int N_j = 8;

	for( int i = 0; i < N_i; ++i )
	{
		float v = i / float( N_i ) * pi;

		for( int j = 0; j < N_j; ++j )
		{
			float w = j / float( N_j ) * pi;

			VECTOR P = I() * cosf( w ) * cosf( v ) +
					   J() * cosf( w ) * sinf( v ) +
					   K() * sinf( w );

			g_pGame->graphics()->Line( m_Pos - m_rad * P, m_Pos + m_rad * P );
		}
	}
}
