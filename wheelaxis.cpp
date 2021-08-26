#include "WheelAxis.h"


WheelAxis :: WheelAxis( VECTOR &Pos ) : RigidSystem( Pos )
{
	float width = 2.0f;

	float dw = 0.5f * width;
	float r  = 0.5f;
	float m  = 25.0f;

	m_pW1 = new Wheel( Pos + VECTOR(-dw, 0, 0 ), m, r );
	m_pW2 = new Wheel( Pos + VECTOR( dw, 0, 0 ), m, r );

//	m_pW1 = new Atom( Pos + VECTOR(-dw, 0, 0 ), 10.0f );
//	m_pW2 = new Atom( Pos + VECTOR( dw, 0, 0 ), 10.0f );

	addObject( m_pW1 );
	addObject( m_pW2 );

	define();
	m_k = 1.0f;

//	m_pW1->setRotationAxis( m_pW1->pSpace()->pI() );
//	m_pW2->setRotationAxis( m_pW1->pSpace()->pI() );
}


WheelAxis :: ~WheelAxis()
{
	delete m_pW1;
	delete m_pW2;
	m_pW1 = m_pW2 = NULL;
}


Wheel* WheelAxis :: LeftWheel()  { return m_pW1; }
Wheel* WheelAxis :: RightWheel() { return m_pW2; }
