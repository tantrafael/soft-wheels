#include "DynamicSystem.h"
#include "Game.h"

extern Game *g_pGame;


//--------------------------------------------------------------------
// Construction, destruction
//--------------------------------------------------------------------
DynamicSystem :: DynamicSystem( VECTOR &Pos ) : ObjectSystem( Pos )
{
//	m_k = 25.0f;
	m_k = 5.0f;
}

DynamicSystem :: ~DynamicSystem()
{}


//--------------------------------------------------------------------
// Methods
//--------------------------------------------------------------------
void DynamicSystem :: addForce( VECTOR &F )
{
	VECTOR A_trans = F / m_mass;

	for( int i = 0; i < m_nrChildren; ++i )
	{
		Object *pChild_i = m_ppChildren[ i ];
		float  m_i = pChild_i->mass();
		VECTOR F_i = m_i * A_trans;

		pChild_i->addForce( F_i );
	}
}


//--------------------------------------------------------------------
void DynamicSystem :: addTorque( VECTOR &T )
{
	addTorque( T, m_Pos );
}


//--------------------------------------------------------------------
void DynamicSystem :: addTorque( VECTOR &T, VECTOR &P )
{
	if( D3DXVec3Length( &T ) > 0.0f )
	{
		VECTOR A_rot = T / inertia( T, P );

		for( int i = 0; i < m_nrChildren; ++i )
		{
			Object *pChild_i = m_ppChildren[ i ];
			float  m_i = pChild_i->mass();
			VECTOR P_i = pChild_i->Pos();
			VECTOR R_i = P_i - P;

			if( D3DXVec3Length( &R_i ) > 0.0f )
			{
				VECTOR A_i;
				D3DXVec3Cross( &A_i, &A_rot, &R_i );
				VECTOR F_i = m_i * A_i;
				pChild_i->addForce( F_i );
			}
		}
	}
}


//--------------------------------------------------------------------
void DynamicSystem :: update()
{
	for( int i = 0; i < m_nrChildren; ++i )
	{
		Object *pChild_i = m_ppChildren[ i ];

		VECTOR P  = pChild_i->Pos();
		VECTOR R0 = m_pR0[ i ];
		VECTOR P0 = m_Pos + R0.x * I() +
							R0.y * J() +
							R0.z * K();
		VECTOR dP = P0 - P;
		float  dp = D3DXVec3Length( &dP );
	//	float  t  = expf( -10.0f * dp );
		float  t  = expf( -1.0f * dp );

		pChild_i->setVelo( t * pChild_i->Velo() );
		pChild_i->addVelo( m_k * dP );
	}

	for( int i = 0; i < m_nrChildren; ++i )
	{
		m_ppChildren[ i ]->update();
	}

	//----------------------------------------------------------------
	m_Pos = masscenter();


	VECTOR W = VECTOR(0,0,0);

	for( int i = 0; i < m_nrChildren; ++i )
	{
		Object *pChild_i = m_ppChildren[ i ];

		VECTOR P_i  = pChild_i->Pos();
		VECTOR R_i  = P_i - m_Pos;

		VECTOR R0_i = m_pR0[ i ].x * I()
					+ m_pR0[ i ].y * J()
					+ m_pR0[ i ].z * K();

		float  r_i  = D3DXVec3Length( &R_i );
		float  r0_i = D3DXVec3Length( &R0_i );

		if( fabs( r0_i * r_i ) > 0.01f )
		{	
			VECTOR R0_ixR_i;
			D3DXVec3Cross( &R0_ixR_i, &R0_i, &R_i );

			VECTOR Axis_i;
			D3DXVec3Normalize( &Axis_i, &R0_ixR_i );

			float sin_angle_i = D3DXVec3Length( &R0_ixR_i ) / ( r0_i * r_i );
			float angle_i     = asinf( sin_angle_i );

			W += angle_i * Axis_i;
		}
	}

	W = W / float( m_nrChildren );

	spin( W );
}


//--------------------------------------------------------------------
void DynamicSystem :: render()
{
	ObjectSystem :: render();
}


/*
//--------------------------------------------------------------------
void DynamicSystem :: update()
{
	for( int i = 0; i < m_nrChildren; ++i )
	{
		Object *pChild = m_ppChildren[ i ];

		VECTOR P = pChild->Pos();
		VECTOR R = P - m_Pos;
		VECTOR F = pChild->Force();
		float r2 = D3DXVec3LengthSq( &R );

	//	VECTOR F_rad = R * D3DXVec3Dot( &F, &R ) / r2;
	//	addForce( F_rad );
		addForce( F );

		VECTOR T;
		D3DXVec3Cross( &T, &R, &F );
		addTorque( T );
	}

//	Body :: update();

	//----------------------------------------------------------------
	m_e = 0.96f;

//	m_Velo  = m_e * m_Velo;
//	m_Omega = m_e * m_Omega;

	//----------------------------------------------------------------
	for( int i = 0; i < m_nrChildren; ++i )
	{
		Object *pChild = m_ppChildren[ i ];

		pChild->update();

		// Fix orientation
		//------------------------------------------------------------
		if( pChild->pRotAxis() )
		{
			VECTOR W;
			D3DXVec3Cross( &W, pChild->pA(), pChild->pRotAxis() );

			if( D3DXVec3Length( &W ) > 0.0f )
			{
				pChild->spin( W );
			}
		}

		// Fix position
		//------------------------------------------------------------
		VECTOR P  = pChild->Pos();
		VECTOR R0 = m_pR0[ i ];
		VECTOR P0 = m_Pos + R0.x * I() + R0.y * J() + R0.z * K();
		VECTOR dP = P0 - P;
		float dp2 = D3DXVec3LengthSq( &dP );

		pChild->move( dP );

	}
}
*/
