#include "Space.h"


Space :: Space()
{
	m_I = VECTOR( 1.0f, 0, 0 );
	m_J = VECTOR( 0, 1.0f, 0 );
	m_K = VECTOR( 0, 0, 1.0f );
	m_n = 0;
}

Space :: ~Space() {}


VECTOR Space :: I() { return m_I; }
VECTOR Space :: J() { return m_J; }
VECTOR Space :: K() { return m_K; }

VECTOR* Space :: pI() { return &m_I; }
VECTOR* Space :: pJ() { return &m_J; }
VECTOR* Space :: pK() { return &m_K; }

void Space :: setI( VECTOR &V ) { m_I = V; }
void Space :: setJ( VECTOR &V ) { m_J = V; }
void Space :: setK( VECTOR &V ) { m_K = V; }

void Space :: rotate( VECTOR &W )
{
	MATRIX R;
	D3DXMatrixRotationAxis( &R, &W, D3DXVec3Length( &W ) );

//	VECTOR result;
//	m_I = *D3DXVec3TransformCoord( &result, &m_I, &R );
//	m_J = *D3DXVec3TransformCoord( &result, &m_J, &R );
//	m_K = *D3DXVec3TransformCoord( &result, &m_K, &R );
	D3DXVec3TransformCoord( &m_I, &m_I, &R );
	D3DXVec3TransformCoord( &m_J, &m_J, &R );
	D3DXVec3TransformCoord( &m_K, &m_K, &R );

//	m_i.normate();		// För att
//	m_j.normate();		// undvika
//	m_k.normate();		// avrundningsfel

//	++m_n;

//	if( m_n > 1000 )
//	{
		normalize();
//		m_n = 0;
//	}
}


void Space :: normalize()
{
	D3DXVec3Normalize( &m_I, &m_I );
	D3DXVec3Normalize( &m_J, &m_J );
	D3DXVec3Cross( &m_K, &m_I, &m_J );
	D3DXVec3Cross( &m_J, &m_K, &m_I );
}
