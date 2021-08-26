#include "Car.h"
#include "Game.h"

extern Game *g_pGame;


//--------------------------------------------------------------------
// Construction, destruction
//--------------------------------------------------------------------
//Car :: Car( VECTOR &Pos ) : ObjectSystem( Pos )
Car :: Car( VECTOR &Pos ) : RigidSystem( Pos )
//Car :: Car( VECTOR &Pos ) : BindingSystem( Pos )
{
	float W = 1.75f;
	float L = 3.25f;
	float H = 1.25f;
	float M = 1000.0f;

	VECTOR dW( 0.5f * W, 0, 0 );
	VECTOR dL( 0, 0.5f * L, 0 );
	VECTOR dH( 0, 0, 0.5f * H );

/*
	// Chassi
	m_pChassi = new Block( Pos, W, L, 1.0f, 100.0f );
//	m_pChassi = new Block( Pos + 0.5f * K(), 1.15f * W, 1.5f * L, 1.0f, 25.0f );
	addObject( m_pChassi );
*/

/*
//	float m = 0.125f * 25.0f;
	float m = 1.0f;
	float k = 1.0f * m;
	m_pA1 = new Atom( Pos - dW + dL + dH, m, k );
	m_pA2 = new Atom( Pos + dW + dL + dH, m, k );
	m_pA3 = new Atom( Pos - dW - dL + dH, m, k );
	m_pA4 = new Atom( Pos + dW - dL + dH, m, k );
	m_pA5 = new Atom( Pos - dW + dL - dH, m, k );
	m_pA6 = new Atom( Pos + dW + dL - dH, m, k );
	m_pA7 = new Atom( Pos - dW - dL - dH, m, k );
	m_pA8 = new Atom( Pos + dW - dL - dH, m, k );

	addObject( m_pA1 );
	addObject( m_pA2 );
	addObject( m_pA3 );
	addObject( m_pA4 );
	addObject( m_pA5 );
	addObject( m_pA6 );
	addObject( m_pA7 );
	addObject( m_pA8 );
*/

/*
	float b = 1.0f;

	for( int i = 0; i < m_nrChildren - 1; ++i )
	{
		for( int j = i + 1; j < m_nrChildren; ++j )
		{
			Bind( m_ppChildren[ i ], m_ppChildren[ j ], b );
		}
	}
*/

/*
	Bind( m_pA1, m_pA2, b );
	Bind( m_pA3, m_pA4, b );
	Bind( m_pA1, m_pA3, b );
	Bind( m_pA2, m_pA4, b );

	Bind( m_pA5, m_pA6, b );
	Bind( m_pA7, m_pA8, b );
	Bind( m_pA5, m_pA7, b );
	Bind( m_pA6, m_pA8, b );

	Bind( m_pA1, m_pA5, b );
	Bind( m_pA2, m_pA6, b );
	Bind( m_pA3, m_pA7, b );
	Bind( m_pA4, m_pA8, b );

	Bind( m_pA1, m_pA8, b );
	Bind( m_pA2, m_pA7, b );
	Bind( m_pA3, m_pA6, b );
	Bind( m_pA4, m_pA5, b );
*/

//	m_pA1->setPos( m_pA1->Pos() + VECTOR(1.0f,0,0) );

	// Wheels
	float m = 10.0f;
	float r = 0.5f;

	m_pW1 = new Wheel( Pos - dW + dL - dH, m, r );
	m_pW2 = new Wheel( Pos + dW + dL - dH, m, r );
	m_pW3 = new Wheel( Pos - dW - dL - dH, m, r );
	m_pW4 = new Wheel( Pos + dW - dL - dH, m, r );

	addObject( m_pW1 );
	addObject( m_pW2 );
	addObject( m_pW3 );
	addObject( m_pW4 );

/*
	m_pWheelAxis1 = new RigidSystem();
	m_pWheelAxis1->addObject( m_pW1 );
	m_pWheelAxis1->addObject( m_pW2 );
	m_pWheelAxis1->define();
//	addObject( m_pWheelAxis1 );

	m_pWheelAxis2 = new RigidSystem();
	m_pWheelAxis2->addObject( m_pW3 );
	m_pWheelAxis2->addObject( m_pW4 );
	m_pWheelAxis2->define();
//	addObject( m_pWheelAxis2 );

	m_pWheelSystem = new RigidSystem();
	m_pWheelSystem->addObject( m_pWheelAxis1 );
	m_pWheelSystem->addObject( m_pWheelAxis2 );
	m_pWheelSystem->define();

	addObject( m_pWheelSystem );
*/

/*
	// Steering wheel
//	m_pFrontWheels = new Wheel( pos + dL, 1.0f, r );
//	addObject( m_pFrontWheels );
	m_pSteeringWheel = new Body();
	m_pSteeringWheel->setInertia( 5.0f );

	float k  = 1.0f;
	float k1 = 2.0f;
	float k2 = 0.5f;

	Bind( m_pW1, m_pChassi->child( 0 ), k );
	Bind( m_pW1, m_pChassi->child( 1 ), k );
	Bind( m_pW1, m_pChassi->child( 2 ), k );

	Bind( m_pW2, m_pChassi->child( 1 ), k );
	Bind( m_pW2, m_pChassi->child( 0 ), k );
	Bind( m_pW2, m_pChassi->child( 3 ), k );

	Bind( m_pW3, m_pChassi->child( 2 ), k );
	Bind( m_pW3, m_pChassi->child( 3 ), k );
	Bind( m_pW3, m_pChassi->child( 0 ), k );

	Bind( m_pW4, m_pChassi->child( 3 ), k );
	Bind( m_pW4, m_pChassi->child( 2 ), k );
	Bind( m_pW4, m_pChassi->child( 1 ), k );
*/

//	Bind( m_pW1, m_pChassi->child( 4 ), k1 );
//	Bind( m_pW1, m_pChassi->child( 5 ), k2 );
//	Bind( m_pW1, m_pChassi->child( 6 ), k2 );

//	Bind( m_pW2, m_pChassi->child( 5 ), k1 );
//	Bind( m_pW2, m_pChassi->child( 4 ), k2 );
//	Bind( m_pW2, m_pChassi->child( 7 ), k2 );

//	Bind( m_pW3, m_pChassi->child( 6 ), k1 );
//	Bind( m_pW3, m_pChassi->child( 7 ), k2 );
//	Bind( m_pW3, m_pChassi->child( 4 ), k2 );

//	Bind( m_pW4, m_pChassi->child( 7 ), k1 );
//	Bind( m_pW4, m_pChassi->child( 6 ), k2 );
//	Bind( m_pW4, m_pChassi->child( 5 ), k2 );

/*
//	Bind( m_pW1, m_pW2, k );
//	Bind( m_pW3, m_pW4, k );
	Bind( m_pW1, m_pW3, k );
	Bind( m_pW2, m_pW4, k );
	Bind( m_pW1, m_pW4, k );
	Bind( m_pW2, m_pW3, k );
*/

//	k = 2.5f;
/*
	Bind( m_pW1, m_pChassi->child( 5 ), k );
	Bind( m_pW2, m_pChassi->child( 4 ), k );
	Bind( m_pW3, m_pChassi->child( 6 ), k );
	Bind( m_pW4, m_pChassi->child( 7 ), k );
*/

/*
	Bind( m_pW1, m_pChassi->child( 4 ), k );
	Bind( m_pW1, m_pChassi->child( 5 ), k );
	Bind( m_pW1, m_pChassi->child( 6 ), k );
	Bind( m_pW1, m_pChassi->child( 7 ), k );
	Bind( m_pW2, m_pChassi->child( 4 ), k );
	Bind( m_pW2, m_pChassi->child( 5 ), k );
	Bind( m_pW2, m_pChassi->child( 6 ), k );
	Bind( m_pW2, m_pChassi->child( 7 ), k );
	Bind( m_pW3, m_pChassi->child( 4 ), k );
	Bind( m_pW3, m_pChassi->child( 5 ), k );
	Bind( m_pW3, m_pChassi->child( 6 ), k );
	Bind( m_pW3, m_pChassi->child( 7 ), k );
	Bind( m_pW4, m_pChassi->child( 4 ), k );
	Bind( m_pW4, m_pChassi->child( 5 ), k );
	Bind( m_pW4, m_pChassi->child( 6 ), k );
	Bind( m_pW4, m_pChassi->child( 7 ), k );
*/

	//----------------------------------------------------------------
//	m_pFrontWheels->setRotAxis( m_pFrontWheels->pSpace()->pK(), m_pSpace->pK() );

//	m_pW1->setRotAxis( m_pW1->pSpace()->pI(), m_pFrontWheels->pSpace()->pI() );
//	m_pW2->setRotAxis( m_pW2->pSpace()->pI(), m_pFrontWheels->pSpace()->pI() );
//	m_pW1->setRotAxis( m_pW1->pSpace()->pI(), m_pSpace->pI() );
//	m_pW2->setRotAxis( m_pW2->pSpace()->pI(), m_pSpace->pI() );
//	m_pW3->setRotAxis( m_pW3->pSpace()->pI(), m_pSpace->pI() );
//	m_pW4->setRotAxis( m_pW4->pSpace()->pI(), m_pSpace->pI() );

	//----------------------------------------------------------------
//	m_k = 20.0f;

	define();
}

Car :: ~Car() {}


//--------------------------------------------------------------------
// Properties
//--------------------------------------------------------------------


//--------------------------------------------------------------------
// Methods
//--------------------------------------------------------------------
void Car :: forward()
{
//	addForce( 1.0f * J() );

	float  k  = -200.0f;
	VECTOR T1 = k * m_pW1->I();
	VECTOR T2 = k * m_pW2->I();
	VECTOR T3 = k * m_pW3->I();
	VECTOR T4 = k * m_pW4->I();

	m_pW1->addTorque( T1 );
	m_pW2->addTorque( T2 );
//	m_pW3->addTorque( T3 );
//	m_pW4->addTorque( T4 );

//	addForce( 1.0f * J() );
//	m_pChassi->addForce( 1.0f * J() );
	
//	addTorque( -T1, m_pW1->Pos() );
//	addTorque( -T2, m_pW1->Pos() );
//	addTorque( -T3, m_pW1->Pos() );
//	addTorque( -T4, m_pW1->Pos() );
}


//--------------------------------------------------------------------
void Car :: back()
{
//	addForce( -1.0f * J() );

	float  k  = 100.0f;
	VECTOR T1 = k * m_pW1->I();
	VECTOR T2 = k * m_pW2->I();
	VECTOR T3 = k * m_pW3->I();
	VECTOR T4 = k * m_pW4->I();

	m_pW1->addTorque( T1 );
	m_pW2->addTorque( T2 );
//	m_pW3->addTorque( T3 );
//	m_pW4->addTorque( T4 );

//	addForce( -1.0f * J() );

/*
	m_pW1->addTorque( 0.1f * m_pW1->I() );
	m_pW2->addTorque( 0.1f * m_pW2->I() );
	m_pW3->addTorque( 0.1f * m_pW3->I() );
	m_pW4->addTorque( 0.1f * m_pW4->I() );
*/

}


//--------------------------------------------------------------------
void Car :: left()
{
	float k = 50.0f;

//	m_pW1->addTorque( 0.1f * m_pWheelAxis1->K() );
//	m_pW2->addTorque( 0.1f * m_pWheelAxis1->K() );
	m_pW1->addTorque( k * K() );
	m_pW2->addTorque( k * K() );

//	m_pSteeringWheel->addTorque( 0.05f * K() );

//	m_pFrontWheels->addTorque( 0.001f * m_pFrontWheels->K() );
}


//--------------------------------------------------------------------
void Car :: right()
{
	float k = 50.0f;

//	m_pW1->addTorque(-0.1f * m_pWheelAxis1->K() );
//	m_pW2->addTorque(-0.1f * m_pWheelAxis1->K() );
	m_pW1->addTorque(-k * K() );
	m_pW2->addTorque(-k * K() );

//	m_pSteeringWheel->addTorque( -0.05f * K() );

//	m_pFrontWheels->addTorque( -0.001f * m_pFrontWheels->K() );
}


//--------------------------------------------------------------------
void Car :: forceToAxis( Object *pObject, VECTOR &A, float k )
{

/*
//	VECTOR A = pObject->pRotAxis();
	VECTOR B = pObject->I();

	float d = D3DXVec3Dot( &B, &A );
	if( fabs( d ) < 1.0f )
	{
		VECTOR W;
		D3DXVec3Cross( &W, &B, &A );

		pObject->addTorque( k * W );
	}

//	pObject->pSpace()->setI( A );
*/

	VECTOR B = pObject->I();

	float d = D3DXVec3Dot( &B, &A );
	if( fabs( d ) < 1.0f )
	{
		VECTOR W;
		D3DXVec3Cross( &W, &B, &A );
		pObject->pSpace()->rotate( W );
	}
}


//--------------------------------------------------------------------
void Car :: forceToPlane( Object *pObject, VECTOR &N, float k )
{
//	VECTOR A = pObject->pRotAxis();
	VECTOR A = pObject->I();

	float d = D3DXVec3Dot( &A, &N );

	if( fabs( d ) > 0.0f )
	{
		VECTOR W;
		D3DXVec3Cross( &W, &N, &A );
		D3DXVec3Normalize( &W, &W );

		pObject->addTorque( k * d * W );
	}
}


//--------------------------------------------------------------------
void Car :: alignToAxis( Object *pObject, VECTOR &P, VECTOR &A )
{
	VECTOR D  = pObject->Pos() - P;
	float  f  = D3DXVec3Dot( &A, &D );
	pObject->setPos( P + f * A );
}


//--------------------------------------------------------------------
void Car :: update()
{
/*
	//Steering wheel
	//----------------------------------------------------------------
	VECTOR I_wheel = m_pSteeringWheel->I();
	VECTOR I_world = VECTOR( 1.0f, 0, 0 );

	float d = D3DXVec3Dot( &I_wheel, &I_world );
	if( fabs( d ) < 1.0f )
	{
		VECTOR W;
		D3DXVec3Cross( &W, &I_wheel, &I_world );
		m_pSteeringWheel->addTorque( 0.075f * W );
	}

//	m_pSteeringWheel->addTorque( -1.0f * m_pSteeringWheel->Omega() );
//	m_pSteeringWheel->setOmega( 0.25f * m_pSteeringWheel->Omega() );

	m_pSteeringWheel->update();
*/

	//----------------------------------------------------------------
/*
	I_wheel = m_pSteeringWheel->I();

	VECTOR A = I_wheel.x * m_pWheelSystem->I() +
			   I_wheel.y * m_pWheelSystem->J() +
			   I_wheel.z * m_pWheelSystem->K();

	float k = 5.0f;
	forceToAxis( m_pW1, A, k );
	forceToAxis( m_pW2, A, k );
	forceToAxis( m_pW3, m_pWheelAxis2->I(), k );
	forceToAxis( m_pW4, m_pWheelAxis2->I(), k );
*/

/*
	I_wheel = m_pSteeringWheel->I();

	VECTOR A = I_wheel.x * m_pWheelAxis1->I() +
			   I_wheel.y * m_pWheelAxis1->J() +
			   I_wheel.z * m_pWheelAxis1->K();

	float k1 = 0.5f;
	float k2 = 2.5f;
//	forceToAxis( m_pW1, A, k1 );
//	forceToAxis( m_pW2, A, k1 );
	forceToAxis( m_pW1, m_pWheelAxis1->I(), k1 );
	forceToAxis( m_pW2, m_pWheelAxis1->I(), k1 );
	forceToAxis( m_pW3, m_pWheelAxis2->I(), k2 );
	forceToAxis( m_pW4, m_pWheelAxis2->I(), k2 );
*/

/*
	I_wheel = m_pSteeringWheel->I();

	VECTOR A = I_wheel.x * I() +
			   I_wheel.y * J() +
			   I_wheel.z * K();

	float k = 5.0f;
	forceToAxis( m_pW1, A, k );
	forceToAxis( m_pW2, A, k );
	forceToAxis( m_pW3, I(), k );
	forceToAxis( m_pW4, I(), k );
*/

	//----------------------------------------------------------------
/*
	addForce( -2.5f * m_Velo );

	if( D3DXVec3LengthSq( &m_Omega ) > 0.0f )
	{
		addTorque( -2.5f * m_Omega );
	}
*/

	//----------------------------------------------------------------
//	ObjectSystem  :: update();
	RigidSystem   :: update();
//	BindingSystem :: update();

	//----------------------------------------------------------------
/*
	alignToAxis( m_pW1, m_pChassi->child( 4 )->Pos(), m_pChassi->K() );
	alignToAxis( m_pW2, m_pChassi->child( 5 )->Pos(), m_pChassi->K() );
	alignToAxis( m_pW3, m_pChassi->child( 6 )->Pos(), m_pChassi->K() );
	alignToAxis( m_pW4, m_pChassi->child( 7 )->Pos(), m_pChassi->K() );
*/

/*
	alignToAxis( m_pW1, m_pA5->Pos(), K() );
	alignToAxis( m_pW2, m_pA6->Pos(), K() );
	alignToAxis( m_pW3, m_pA7->Pos(), K() );
	alignToAxis( m_pW4, m_pA8->Pos(), K() );
*/
	//----------------------------------------------------------------
//	m_pSpace->setI( m_pWheelSystem->I() );
//	m_pSpace->setJ( m_pWheelSystem->J() );
//	m_pSpace->setK( m_pWheelSystem->K() );
}


//--------------------------------------------------------------------
void Car :: render()
{
//	ObjectSystem  :: render();
	RigidSystem   :: render();
//	BindingSystem :: render();

/*
	m_pB1->render();
	m_pB2->render();
	m_pB3->render();
	m_pB4->render();
*/
}
