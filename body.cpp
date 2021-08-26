#include "Body.h"
#include "Space.h"
#include "Game.h"

extern Game *g_pGame;


//------------------------------------------------------------
// Construction, destruction
//------------------------------------------------------------
Body :: Body()
{
	m_inertia   = 0.0f;
	m_pSpace    = new Space();
	m_Torque    = VECTOR(0,0,0);
	m_Alpha     = VECTOR(0,0,0);
	m_Omega     = VECTOR(0,0,0);
	m_RotCenter = m_Pos;
}

Body :: Body( VECTOR &pos, float mass ) : Mass( pos, mass )
{
	m_inertia   = 0.0f;
	m_pSpace    = new Space();
	m_Torque    = VECTOR(0,0,0);
	m_Alpha     = VECTOR(0,0,0);
	m_Omega     = VECTOR(0,0,0);
	m_RotCenter = m_Pos;
}

Body :: ~Body() {}


//------------------------------------------------------------
// Properties
//------------------------------------------------------------
float  Body :: inertia( VECTOR &A ) { return m_inertia; }

Space* Body :: pSpace() { return m_pSpace; }
VECTOR Body :: I() { return m_pSpace->I(); }
VECTOR Body :: J() { return m_pSpace->J(); }
VECTOR Body :: K() { return m_pSpace->K(); }

VECTOR Body :: Omega  () { return m_Omega;  }
VECTOR Body :: Torque () { return m_Torque; }


//------------------------------------------------------------
// Methods
//------------------------------------------------------------
void Body :: setInertia ( float   i ) { m_inertia = i; }

void Body :: setSpace (Space *pSpace) { m_pSpace = pSpace; }

void Body :: setOmega   ( VECTOR &W ) { m_Omega   = W; }
void Body :: setTorque  ( VECTOR &T ) { m_Torque  = T; }
void Body :: addOmega   ( VECTOR &W ) { m_Omega  += W; }
void Body :: addTorque  ( VECTOR &T ) { m_Torque += T; }

void Body :: addTorque  ( VECTOR &T, VECTOR &P )
{
	m_Torque    += T;
	m_RotCenter += P;
}


//--------------------------------------------------------------------
void Body :: forceToAxis( VECTOR &A, float f )
{
//	VECTOR A = pObject->pRotAxis();
	VECTOR B = I();

	float d = D3DXVec3Dot( &B, &A );
	if( fabs( d ) < 1.0f )
	{
		VECTOR W;
		D3DXVec3Cross( &W, &B, &A );
		addTorque( f * W );
	}
}


//--------------------------------------------------------------------
void Body :: forceToPlane( VECTOR &N, float f )
{
//	VECTOR A = pObject->pRotAxis();
	VECTOR B = I();

	float d = D3DXVec3Dot( &B, &N );

	if( fabs( d ) > 0.0f )
	{
		VECTOR W;
		D3DXVec3Cross( &W, &N, &B );
		D3DXVec3Normalize( &W, &W );
		addTorque( f * d * W );
	}
}


//------------------------------------------------------------
void Body :: spin( VECTOR &W )
{
//	rotate( W, m_Pos );
	m_pSpace->rotate( W );
}


//------------------------------------------------------------
void Body :: rotate( VECTOR &W, VECTOR &P )
{
	VECTOR D = m_Pos - P;
	
	if( D3DXVec3Length( &D ) > 0.0f )
	{
		Mass :: rotate( W, P );
	}

	m_pSpace->rotate( W );
}


//------------------------------------------------------------
void Body :: update_rot()
{
	float dt  = g_pGame->world()->dt();
	float dt2 = g_pGame->world()->dt2();
	float timeconst = g_pGame->world()->timeconst();

/*
	if( D3DXVec3LengthSq( &m_Omega ) > 0 )
	{
		spin( m_Omega * dt );
	}

	m_Omega = m_Omega + m_Alpha * dt;

	if( D3DXVec3LengthSq( &m_Torque ) > 0 )
	{
		m_Alpha = m_Torque / inertia( m_Torque );
	}
	else
	{
		m_Alpha = VECTOR(0,0,0);
	}
*/

	if( D3DXVec3LengthSq( &m_Torque ) > 0 )
	{
		m_Alpha = m_Torque / inertia( m_Torque );
	}
	else
	{
		m_Alpha = VECTOR(0,0,0);
	}

	m_Omega = m_Omega + m_Alpha * dt;

	if( D3DXVec3LengthSq( &m_Omega ) > 0 )
	{
		spin( m_Omega * dt );
	}


	m_Torque = VECTOR(0,0,0);
}


//------------------------------------------------------------
void Body :: update()
{
	update_trans();
	update_rot();
}


//------------------------------------------------------------
void Body :: render()
{
	float k = 0.25f;

	VECTOR dI = k * I();
	VECTOR dJ = k * J();
	VECTOR dK = k * K();

	g_pGame->graphics()->Line( m_Pos - dI, m_Pos + dI );
	g_pGame->graphics()->Line( m_Pos - dJ, m_Pos + dJ );
	g_pGame->graphics()->Line( m_Pos - dK, m_Pos + dK );
}
