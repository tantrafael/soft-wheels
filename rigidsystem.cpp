#include "RigidSystem.h"
#include "Game.h"
#include <list.h>

extern Game *g_pGame;

int n = 0;


//--------------------------------------------------------------------
// Construction, destruction
//--------------------------------------------------------------------
RigidSystem :: RigidSystem()
{
	m_ppAtoms = new Object* [ 1000 ];
	m_nrAtoms = 0;
	m_k       = 1.0f;

	m_CollisionPoint = VECTOR(0,0,0);

	m_pA       = NULL;
	m_pRotAxis = NULL;
}

RigidSystem :: RigidSystem( VECTOR &Pos ) : ObjectSystem( Pos )
{
	m_ppAtoms = new Object* [ 1000 ];
	m_nrAtoms = 0;
	m_k       = 1.0f;

	m_CollisionPoint = VECTOR(0,0,0);

	m_pA       = NULL;
	m_pRotAxis = NULL;
}

RigidSystem :: ~RigidSystem()
{
	for( int n = 0; n < m_nrAtoms; ++n )
	{
		delete m_ppAtoms[ n ];
	}

	m_nrAtoms = 0;
	m_ppAtoms = NULL;
}


//--------------------------------------------------------------------
// Properties
//--------------------------------------------------------------------
VECTOR RigidSystem :: Force()
{
	VECTOR F(0,0,0);

	for( int i = 0; i < m_nrChildren; ++i )
	{
		Object *pChild_i = m_ppChildren[ i ];

		VECTOR P_i = pChild_i->Pos();
		VECTOR R_i = P_i - m_Pos;
		VECTOR F_i = pChild_i->Force();
		float r2_i = D3DXVec3LengthSq( &R_i );

		if( P_i.z < 0.0f )
		{
			VECTOR A;
			D3DXVec3Cross( &A, &R_i, &m_Omega );
			F += 0.1f * A;

		//	VECTOR B;
		//	D3DXVec3Cross( &B, &m_Velo, &R_i );
		//	T += 0.1f * B;
		}

	//	F += R_i * D3DXVec3Dot( &F_i, &R_i ) / r2_i;
		F += F_i;
	}

	for( int i = 0; i < m_nrBindings; ++i )
	{
		F += m_ppBindings[ i ]->Force( this );
	}

	return F;
}

//--------------------------------------------------------------------
VECTOR RigidSystem :: MostCollidedPoint()
{
	VECTOR P_min = VECTOR(0,0,0);

	for( int i = 0; i < m_nrChildren; ++i )
	{
		VECTOR P_min_i = m_ppChildren[ i ]->MostCollidedPoint();

		if( P_min_i.z < P_min.z )
		{
			P_min = P_min_i;
		}
	}

	return P_min;
}

//--------------------------------------------------------------------
VECTOR* RigidSystem :: pRotAxis () { return m_pRotAxis; }
VECTOR* RigidSystem :: pA       () { return m_pA;       }

//--------------------------------------------------------------------
// Methods
//--------------------------------------------------------------------
void RigidSystem :: move( VECTOR &V )
{
	Mass :: move( V );
}

//--------------------------------------------------------------------
void RigidSystem :: setPos( VECTOR &P )
{
	m_Pos = P;

	for( int i = 0; i < m_nrChildren; ++i )
	{
		Object *pChild_i = m_ppChildren[ i ];

		VECTOR R0_i = m_pR0[ i ];
		VECTOR P_i  = m_Pos + R0_i.x * I()
							+ R0_i.y * J()
							+ R0_i.z * K();

		pChild_i->setPos( P_i );
	}
}

//--------------------------------------------------------------------
void RigidSystem :: setRotAxis( VECTOR *pA, VECTOR *pRotAxis )
{
	m_pA       = pA;
	m_pRotAxis = pRotAxis;
}

//--------------------------------------------------------------------
void RigidSystem :: update()
{
	addForce( m_mass * g_pGame->world()->gravity() );
//	m_addExternalForces();

	Body :: update();

	for( int i = 0; i < m_nrChildren; ++i )
	{
		m_ppChildren[ i ]->update_rot();
	}

	setPos( m_Pos );

	VECTOR N     = VECTOR( 0, 0, 1.0f );
	VECTOR P_min = MostCollidedPoint();

	if( P_min.z < 0.0f )
	{
		VECTOR dP   = m_Pos - m_Pos_1;
		float  dp_N = dP.z;

		if( fabs( dp_N ) > 0.001f )
		{
			VECTOR D;
			D3DXVec3Normalize( &D, &dP );
			float  dp  = D3DXVec3Length( &dP );
			float  e_N = P_min.z;
			float  e   = e_N * dp / dp_N;
			float  s   = dp - e;

			m_Pos = m_Pos_1 + s * D;
			setPos( m_Pos );
		//	setPos( m_Pos_1 + s * D );

			// update velocity and rotation
			// changed in collision
		}
	}

	m_Velo  = 0.95f * m_Velo;
	m_Omega = 0.95f * m_Omega;
}

/*
//--------------------------------------------------------------------
void RigidSystem :: m_addExternalForces()
{
	for( int i = 0; i < m_nrChildren; ++i )
	{
		Object *pChild_i = m_ppChildren[ i ];

		VECTOR F_i = pChild_i->Force();		
	}
}
*/

//--------------------------------------------------------------------
void RigidSystem :: m_collisionUpdate()
{
	VECTOR P_min = VECTOR(0,0,0);

	for( int i = 0; i < m_nrChildren; ++i )
	{
		Object *pChild_i = m_ppChildren[ i ];

		VECTOR R0_i = m_pR0[ i ].x * I() +
					  m_pR0[ i ].y * J() +
					  m_pR0[ i ].z * K();

		VECTOR P_i  = m_Pos + R0_i;

		pChild_i->setPos( P_i );

		if( P_i.z < 0.0f )
		{
			if( P_i.z < P_min.z )
			{
				P_min = P_i;
			}
		}
	}

	if( P_min.z < 0.0f )
	{
		float  dt = g_pGame->world()->dt();
		VECTOR N  = VECTOR( 0.0f, 0.0f, 1.0f );

		//------------------------------------------------------------
		m_CollisionPoint = VECTOR(0,0,0);
		VECTOR D_cp(0,0,0);
		int n = 0;

		for( int i = 0; i < m_nrChildren; ++i )
		{
			Object *pChild_i = m_ppChildren[ i ];

			VECTOR P_i = pChild_i->Pos();
			VECTOR D_cp_i = P_i - m_Pos;

			if( fabs( P_i.z - P_min.z ) < 0.001f )
			{
				D_cp = D_cp + D_cp_i;
				n++;
			}
		}

		D_cp = D_cp / float( n );

		//------------------------------------------------------------
		VECTOR dP   = m_Pos - m_Pos_1;
		float  dp_N = dP.z;

		if( fabs( dp_N ) > 0.001f )
		{
			VECTOR D1, D2;
			D3DXVec3Normalize( &D1, &dP );
			D2 = D1 - 2.0f * ( D3DXVec3Dot( &D1, &N ) * N );
			float  dp   = D3DXVec3Length( &dP );
			float  e_N  = P_min.z;
			float  e    = e_N * dp / dp_N;
			float  s    = dp - e;

		//	VECTOR E  = e * D1;
			VECTOR P0 = m_Pos_1 + s * D1;
		//	VECTOR P1 = P0 + e * D2;

			VECTOR E  = P0 - m_Pos;

		//	m_Pos += E;
			m_Pos = P0;
		//	m_Pos = P1;
		}
		else
		{
			VECTOR P_cp = m_Pos + D_cp;
			m_Pos.z += P_cp.z;
		}
		
		m_CollisionPoint = m_Pos + D_cp;

		//------------------------------------------------------------
		VECTOR R_cp = m_CollisionPoint - m_Pos;
		VECTOR R1_cp;
		D3DXVec3Normalize( &R1_cp, &R_cp );
		float  r_cp = D3DXVec3Length( &R_cp );

		VECTOR V_cp_rad = m_Velo;
		VECTOR V_cp_rot;
		D3DXVec3Cross( &V_cp_rot, &m_Omega, &R_cp );
		VECTOR V_cp = V_cp_rad + V_cp_rot;

	//	VECTOR dV_cp  = -2.0f * D3DXVec3Dot( &V_cp, &N ) * N;
		VECTOR dV_cp  = -1.5f * D3DXVec3Dot( &V_cp, &N ) * N;

		if( D3DXVec3Length( &dV_cp ) > 0.001f )
		{
			VECTOR dV = D3DXVec3Dot( &dV_cp, &R1_cp ) * R1_cp;
		//	m_Velo += dV;
			m_Velo.z += dV.z;

			VECTOR dW;
			D3DXVec3Cross( &dW, &R1_cp, &dV_cp );
			m_Omega += dW;
		}
	}
}


//--------------------------------------------------------------------
void RigidSystem :: render()
{
	ObjectSystem :: render();
//	g_pGame->graphics()->Line( m_Pos, m_CollisionPoint );
}
