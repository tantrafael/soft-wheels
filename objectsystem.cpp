#include "ObjectSystem.h"
#include "Game.h"

extern Game *g_pGame;


//--------------------------------------------------------------------
// Construction, destruction
//--------------------------------------------------------------------
ObjectSystem :: ObjectSystem()
{
	m_nrChildren        = 0;
	m_ppChildren        = new Object* [ 1000 ];
	m_pR0               = NULL;

	m_pDegreesOfFreedom = new int     [ 1000 ];
	m_pFreedomAxis      = new VECTOR  [ 1000 ];
	m_pFreedomPlane     = new PLANE   [ 1000 ];

	for( int i = 0; i < 1000; ++i )
	{
		m_pDegreesOfFreedom [ i ]   = 0;
		m_pFreedomAxis      [ i ]   = VECTOR(0,0,0);
		m_pFreedomPlane     [ i ].P = VECTOR(0,0,0);
		m_pFreedomPlane     [ i ].N = VECTOR(0,0,0);
	}
}

ObjectSystem :: ObjectSystem( VECTOR &Pos ) : Body( Pos, 0.0f )
{
	m_nrChildren        = 0;
	m_ppChildren        = new Object* [ 1000 ];
	m_pR0               = NULL;

	m_pDegreesOfFreedom = new int     [ 1000 ];
	m_pFreedomAxis      = new VECTOR  [ 1000 ];
	m_pFreedomPlane     = new PLANE   [ 1000 ];

	for( int i = 0; i < 1000; ++i )
	{
		m_pDegreesOfFreedom [ i ]   = 0;
		m_pFreedomAxis      [ i ]   = VECTOR(0,0,0);
		m_pFreedomPlane     [ i ].P = VECTOR(0,0,0);
		m_pFreedomPlane     [ i ].N = VECTOR(0,0,0);
	}
}

ObjectSystem :: ~ObjectSystem()
{
	for( int i = 0; i < m_nrChildren; ++i )
	{
		delete m_ppChildren[ i ];
	}

	delete [] m_pR0;

	m_mass        = 0;
	m_nrChildren  = 0;
	m_ppChildren  = NULL;
	m_pR0         = NULL;
}


//--------------------------------------------------------------------
// Properties
//--------------------------------------------------------------------
VECTOR ObjectSystem :: masscenter()
{
	VECTOR P = VECTOR(0,0,0);

	for( int i = 0; i < m_nrChildren; ++i )
	{
		Object *pChild_i = m_ppChildren[ i ];
		P = P + pChild_i->Pos() * pChild_i->mass();
	}

	return P / m_mass;
}


//--------------------------------------------------------------------
float ObjectSystem :: inertia( VECTOR &A )
{
	return inertia( A, m_Pos );
}


//--------------------------------------------------------------------
float ObjectSystem :: inertia( VECTOR &A, VECTOR &P )
{
	float I = 0;

	for( int i = 0; i < m_nrChildren; ++i )
	{
		I += m_ppChildren[ i ]->inertia( A, P );
	}

	return I;
}


//--------------------------------------------------------------------
int ObjectSystem :: children()
{
	return m_nrChildren;
}


//--------------------------------------------------------------------
Object* ObjectSystem :: child( int i )
{
	return m_ppChildren[ i ];
}


//--------------------------------------------------------------------
// Methods
//--------------------------------------------------------------------
void ObjectSystem :: addObject( Object *pObject )
{
	m_ppChildren[ m_nrChildren ] = pObject;
	m_nrChildren++;
	m_mass += pObject->mass();
}


//--------------------------------------------------------------------
void ObjectSystem :: addObject( Object *pObject, VECTOR &FreedomAxis )
{
	m_pDegreesOfFreedom [ m_nrChildren ] = 1;
	m_pFreedomAxis      [ m_nrChildren ] = FreedomAxis;
	addObject( pObject );
}


//--------------------------------------------------------------------
void ObjectSystem :: setTop( Object *pObject )
{
	m_pTop = pObject;

	for( int i = 0; i < m_nrChildren; ++i )
	{
		m_ppChildren[ i ]->setTop( pObject );
	}
}


//--------------------------------------------------------------------
void ObjectSystem :: define()
{
	m_Pos = masscenter();
	m_Pos_1 = m_Pos;

	m_pR0 = new VECTOR[ m_nrChildren ];

	for( int i = 0; i < m_nrChildren; ++i )
	{
		Object *pChild_i = m_ppChildren[ i ];
		m_pR0[ i ] = pChild_i->Pos() - m_Pos;
		pChild_i->setParent( this );
		pChild_i->setTop( this->top() );
	}
}


//--------------------------------------------------------------------
void ObjectSystem :: addForce( VECTOR &F )
{
	Mass :: addForce( F );

/*
	VECTOR A_trans = F / m_mass;

	for( int i = 0; i < m_nrChildren; ++i )
	{
		Object *pChild_i = m_ppChildren[ i ];
		float  m_i = pChild_i->mass();
		VECTOR F_i = m_i * A_trans;

		pChild_i->addForce( F_i );
	}
*/

}


//--------------------------------------------------------------------
void ObjectSystem :: addTorque( VECTOR &T )
{
	addTorque( T, m_Pos );
}


//--------------------------------------------------------------------
void ObjectSystem :: addTorque( VECTOR &T, VECTOR &P )
{
	if( D3DXVec3Length( &T ) > 0.0f )
	{
		Body :: addTorque( T, P );

/*
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
*/
	}
}


//--------------------------------------------------------------------
void ObjectSystem :: move( VECTOR &V )
{
	Mass :: move( V );

//	for( int n = 0; n < m_nrChildren; ++n )
//	{
//		m_ppChildren[ n ]->move( v );
//	}
}


//--------------------------------------------------------------------
void ObjectSystem :: setPos( VECTOR &P )
{
	VECTOR dP = P - m_Pos;

	Mass :: setPos( m_Pos + dP );

	for( int i = 0; i < m_nrChildren; ++i )
	{
		Object *pChild_i = m_ppChildren[ i ];
		pChild_i->setPos( pChild_i->Pos() + dP );
	}
}


//--------------------------------------------------------------------
void ObjectSystem :: rotate( VECTOR &P, VECTOR &W )
{
	Body :: rotate( P, W );

//	for( int n = 0; n < m_nrChildren; ++n )
//	{
//		m_ppChildren[ n ]->rotate( p, w );
//	}
}


//--------------------------------------------------------------------
void ObjectSystem :: update()
{
	Body :: update();

	//----------------------------------------------------------------
	for( int i = 0; i < m_nrChildren; ++i )
	{
		m_ppChildren[ i ]->update();
	}

	/*
	//----------------------------------------------------------------
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

		VECTOR R0_ixR_i;
		D3DXVec3Cross( &R0_ixR_i, &R0_i, &R_i );

		VECTOR Axis_i;
		D3DXVec3Normalize( &Axis_i, &R0_ixR_i );

		float sin_angle_i = D3DXVec3Length( &R0_ixR_i ) / ( r0_i * r_i );
		float angle_i     = asinf( sin_angle_i );

		W += angle_i * Axis_i;
	}

	W = W / float( m_nrChildren );

	spin( W );
	*/

	//----------------------------------------------------------------
//	m_Pos = masscenter();
}


//--------------------------------------------------------------------
void ObjectSystem :: render()
{
	Body :: render();

//	for( int i = 0; i < m_nrChildren; ++i )
//	{
//		Object *pChild_i = m_ppChildren[ i ];
//		g_pGame->graphics()->Line( m_Pos, pChild_i->Pos() );
//	}

	for( int i = 0; i < m_nrChildren; ++i )
	{
		m_ppChildren[ i ]->render();
	}
}
