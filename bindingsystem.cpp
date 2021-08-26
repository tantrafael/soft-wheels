#include "BindingSystem.h"
#include "Game.h"

extern Game *g_pGame;


//--------------------------------------------------------------------
// Construction, destruction
//--------------------------------------------------------------------
BindingSystem :: BindingSystem( VECTOR &Pos ) : ObjectSystem( Pos )
{
	m_ppInternalBindings = new Binding* [ 1000 ];
	m_nrInternalBindings = 0;
}

BindingSystem :: ~BindingSystem()
{
	for( int n = 0; n < m_nrInternalBindings; ++n )
	{
		delete m_ppInternalBindings[ n ];
	}

	m_ppInternalBindings = NULL;
	m_nrInternalBindings = 0;
}


//--------------------------------------------------------------------
// Methods
//--------------------------------------------------------------------
void BindingSystem :: Bind( Object *pObject1, Object *pObject2, float k )
{
	Binding *pBinding = new Binding( pObject1, pObject2, k );
	pBinding->setParent( this );

	pObject1->addBinding( pBinding );
	pObject2->addBinding( pBinding );

	m_ppInternalBindings[ m_nrInternalBindings ] = pBinding;
	m_nrInternalBindings++;
}


//--------------------------------------------------------------------
void BindingSystem :: update()
{
	for( int i = 0; i < m_nrInternalBindings; ++i )
	{
	//	m_ppInternalBindings[ i ]->update();
	}

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
		float  t  = expf( -10.0f * dp );

		pChild_i->setVelo( t * pChild_i->Velo() );
		pChild_i->addVelo( 25.0f * dP );
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
void BindingSystem :: render()
{
	ObjectSystem :: render();

	for( int i = 0; i < m_nrInternalBindings; ++i )
	{
		m_ppInternalBindings[ i ]->render();
	}
}
