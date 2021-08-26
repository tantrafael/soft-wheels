#include "Wheel.h"
#include "Game.h"

extern Game *g_pGame;


//Wheel :: Wheel( VECTOR &Pos, float mass, float radius ) : ObjectSystem( Pos )
Wheel :: Wheel( VECTOR &Pos, float mass, float r ) : RigidSystem( Pos )
//Wheel :: Wheel( VECTOR &Pos, float mass, float r ) : DynamicSystem( Pos )
//Wheel :: Wheel( VECTOR &Pos, float mass, float r ) : BindingSystem( Pos )
{
	m_r1     = r;
	m_r2     = 0.5f * m_r1;
	m_width  = 0.5f;
	m_N      = 4;

	float dm = 0.5f * mass / ( 2 * m_N );
//	float dm = mass / m_N;
	float dw = 0.5f * m_width;
	VECTOR DW = VECTOR( dw, 0, 0 );
	float k  = 100.0f / float( m_N );

//	m_pCylinder1 = new RigidSystem();
//	m_pCylinder2 = new RigidSystem();

//	float k = 1.5f;
	float b = 1.0f;


	for( int i = 0; i < m_N; ++i )
	{
		float  t  = 2*pi * i / float( m_N );
		VECTOR D  = VECTOR( 0, cosf( t ), sinf( t ) );
		VECTOR R1 = D * m_r1;
//		VECTOR R2 = D * m_r2;

		Atom *pA1L = new Atom( Pos + R1 - DW, dm );
		Atom *pA1R = new Atom( Pos + R1 + DW, dm );
//		Atom *pA2L = new Atom( Pos + R2 - DW, dm, k );
//		Atom *pA2R = new Atom( Pos + R2 + DW, dm, k );

		addObject( pA1L );
		addObject( pA1R );
//		addObject( pA1L );
//		addObject( pA1L );

//		m_pCylinder1->addObject( pA1L );
//		m_pCylinder1->addObject( pA1R );
//		m_pCylinder2->addObject( pA2L );
//		m_pCylinder2->addObject( pA2R );

	//	Bind( pA0,  pA1L, b );
	//	Bind( pA0,  pA1R, b );
	//	Bind( pA1L, pA1R, b );
	}

//	Atom *pA0 = new Atom( Pos, 0.5f * mass );
//	addObject( pA0 );

//	m_pCylinder1->define();
//	m_pCylinder2->define();

//	addObject( m_pCylinder1 );
//	addObject( m_pCylinder2 );

	define();

/*
	for( int i = 0; i < m_N; ++i )
	{
		int m = 2 * i + 1;
		int n = ( m + 2 ) % ( 2 * m_N );
		Bind( child( m ), child( n ), b );
		Bind( child( m + 1 ), child( n + 1 ), b );
	}
*/

/*
	for( int i = 0; i < m_N - 1; ++i )
	{
		int m = 2 * i + 1;

		for( int j = i ; j < m_N; ++j )
		{
			int n = i + 2 * j;
	
			Bind( child( i ), child( j ), b );
		}
	}
*/

//	m_ppChildren[ 0 ]->move( VECTOR(0.1f,0,0) );
	
//	m_k = 1.0f;


/*
	m_nVertices   = 2 * m_N;
	m_pVertexList = new vertex[ m_nVertices ];
	for( int n = 0; n < m_nVertices; ++n )
	{
		m_pVertexList[ n ].position = VECTOR(0,0,0);
		m_pVertexList[ n ].normal   = VECTOR(0,0,0);
	}

	Graphics *pGraphics = g_pGame->graphics();
	m_pVertexBuffer = pGraphics->CreateVertexBuffer( m_pVertexList,
													 m_nVertices );


	short *L1 = new short[ m_nVertices + 2 ];
	for( int n = 0; n < m_nVertices + 2; ++n )
	{
		L1[ n ] = n % m_nVertices;
	}


	m_ppIndexBuffers = new IDirect3DIndexBuffer9*[ 1 ];
	m_ppIndexBuffers[ 0 ] = pGraphics->CreateIndexBuffer( L1, m_nVertices + 2 );


	ZeroMemory( &m_material, sizeof( D3DMATERIAL9 ) );
	m_material.Diffuse.r  = 1.0f;
	m_material.Diffuse.g  = 0.0f;
	m_material.Diffuse.b  = 0.0f;
	m_material.Diffuse.a  = 1.0f;
	m_material.Emissive.r = 0.5f;
	m_material.Emissive.g = 0.0f;
	m_material.Emissive.b = 0.0f;
	m_material.Emissive.a = 1.0f;
*/

}

Wheel :: ~Wheel() {}


void Wheel :: update()
{
//	ObjectSystem  :: update();
	RigidSystem   :: update();
//	DynamicSystem :: update();
//	BindingSystem :: update();
}


void Wheel :: render()
{
//	ObjectSystem  :: render();
	RigidSystem   :: render();
//	DynamicSystem :: render();
//	BindingSystem :: render();


/*
	Graphics *pGraphics = g_pGame->graphics();
	IDirect3DDevice9 *pDevice = pGraphics->Device();

	for( int n = 0; n < m_nrChildren; ++n )
	{
		VECTOR P = m_ppChildren[ n ]->Pos();
		VECTOR N = P - m_Pos;
		D3DXVec3Normalize( &N, &N );

		m_pVertexList[ n ].position.x = P.x;
		m_pVertexList[ n ].position.z = P.y;
		m_pVertexList[ n ].position.y = P.z;
		m_pVertexList[ n ].normal.x   = N.x;
		m_pVertexList[ n ].normal.z   = N.y;
		m_pVertexList[ n ].normal.y   = N.z;
	}

	m_pVertexBuffer->Release();
	m_pVertexBuffer = pGraphics->CreateVertexBuffer( m_pVertexList,
													 m_nVertices );


	pDevice->SetStreamSource( 0, m_pVertexBuffer, 0, vertexSize );
	pDevice->SetMaterial( &m_material );

	pDevice->SetIndices( m_ppIndexBuffers[ 0 ] );
	pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP, 0, 0, m_nVertices, 0, m_nVertices );
*/

}
