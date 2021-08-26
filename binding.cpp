#include "Binding.h"
#include "Game.h"

extern Game *g_pGame;

//--------------------------------------------------------------------
// Constructors, destructors
//--------------------------------------------------------------------
Binding :: Binding() {}

Binding :: Binding( Object *p1, Object *p2, float k )
{
	m_pParent = NULL;

	m_p1 = p1;
	m_p2 = p2;

	m_R12 = m_p2->Pos() - m_p1->Pos();
	m_R21 = m_p1->Pos() - m_p2->Pos();

	m_r0 = D3DXVec3Length( &m_R12 );
	
	m_k  = k;
}

Binding :: ~Binding() {}


//--------------------------------------------------------------------
VECTOR Binding :: Force( Object *pObject )
{
	VECTOR F(0,0,0);

	if( ( pObject == m_p1 ) || ( pObject == m_p2 ) )
	{
		Object *pOther;
	//	VECTOR  R0;

		if( pObject == m_p1 )
		{
			pOther = m_p2;
	//		R0 = m_R12;
		}
		else
		{
			pOther = m_p1;
	//		R0 = m_R21;
		}

		VECTOR R = pOther->Pos() - pObject->Pos();
		float  r = D3DXVec3Length( &R );
		float  d = r - m_r0;
		D3DXVec3Normalize( &R, &R );

		float  f = m_k * d;

	//	float  t = D3DXVec3Dot( &R, &R0 );
	//	float  d = r - m_r0;
	//	float  f = m_k * d;

		F = f * R;
	}

	return F;
}


//--------------------------------------------------------------------
// Methods
//--------------------------------------------------------------------
void Binding :: setParent( Object *pObject )
{
	m_pParent = pObject;
}


//--------------------------------------------------------------------
void Binding :: update()
{
/*
	VECTOR R  = m_p2->Pos() - m_p1->Pos();
	float  r  = D3DXVec3Length( &R );
	D3DXVec3Normalize( &R, &R );

	float  d  = m_k * ( r - m_r0 );
	VECTOR dV = d * R;
	float  dv = D3DXVec3Length( &dV );
	float  t  = expf( -0.25f * dv );

	m_p1->addVelo( dV );
	m_p2->addVelo(-dV );

	m_p1->setVelo( t * m_p1->Velo() );
	m_p2->setVelo( t * m_p2->Velo() );
*/

/*
	VECTOR V1 = m_p1->Velo();
	VECTOR V1_R = D3DXVec3Dot( &V1, &R ) * R;
	V1   = V1 - V1_R;
	V1_R = t  * V1_R;
	V1   = V1 + V1_R;

	m_p1->setVelo( V1 + dV );


	VECTOR V2 = m_p2->Velo();
	VECTOR V2_R = D3DXVec3Dot( &V2, &R ) * R;
	V2   = V2 - V2_R;
	V2_R = t  * V2_R;
	V2   = V2 + V2_R;

	m_p1->setVelo( V1 + dV );
*/

}


//--------------------------------------------------------------------
void Binding :: m_update( Object *p1, Object *p2, VECTOR &R12 )
{
	VECTOR R  = p2->Pos() - p1->Pos();
	float  r  = D3DXVec3Length( &R );
	D3DXVec3Normalize( &R, &R );

	//----------------------------------------------------------------
	float  d       = r - m_r0;
	float  f_elong = m_k * d;
	VECTOR F_elong = -f_elong * R;

	p2->addForce( F_elong );
}


//--------------------------------------------------------------------
void Binding :: render()
{
	g_pGame->graphics()->Line( m_p1->Pos(), m_p2->Pos() );
}
