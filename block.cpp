#include "Block.h"
#include "Game.h"

extern Game *g_pGame;


Block :: Block( VECTOR &Pos,
			    float  width,
			    float  length,
				float  height,
				float  mass ) : RigidSystem( Pos )
//				float  mass ) : BindingSystem( Pos )
{
	float dw = 0.5f * width;
	float dl = 0.5f * length;
	float dh = 0.5f * height;
	float dm = mass / 8.0f;

	float k = 0.5f * mass;

	addObject( new Atom( Pos + VECTOR(-dw, dl, dh ), dm ) );
	addObject( new Atom( Pos + VECTOR( dw, dl, dh ), dm ) );
	addObject( new Atom( Pos + VECTOR(-dw, dl, dh ), dm ) );
	addObject( new Atom( Pos + VECTOR( dw, dl, dh ), dm ) );
	addObject( new Atom( Pos + VECTOR(-dw,-dl, dh ), dm ) );
	addObject( new Atom( Pos + VECTOR( dw,-dl, dh ), dm ) );
	addObject( new Atom( Pos + VECTOR(-dw, dl,-dh ), dm ) );
	addObject( new Atom( Pos + VECTOR( dw, dl,-dh ), dm ) );
	addObject( new Atom( Pos + VECTOR(-dw,-dl,-dh ), dm ) );
	addObject( new Atom( Pos + VECTOR( dw,-dl,-dh ), dm ) );

//	float k = 1.0f;

/*
	addBinding( child( 0 ), child( 1 ), k );
	addBinding( child( 1 ), child( 2 ), k );
	addBinding( child( 2 ), child( 3 ), k );
	addBinding( child( 3 ), child( 0 ), k );

	addBinding( child( 4 ), child( 5 ), k );
	addBinding( child( 5 ), child( 6 ), k );
	addBinding( child( 6 ), child( 7 ), k );
	addBinding( child( 7 ), child( 4 ), k );

	addBinding( child( 0 ), child( 6 ), k );
	addBinding( child( 1 ), child( 7 ), k );
	addBinding( child( 2 ), child( 4 ), k );
	addBinding( child( 3 ), child( 5 ), k );
*/

	define();


	m_nVertices   = 8;
	m_pVertexList = new vertex[ m_nVertices ];
	for( int n = 0; n < m_nVertices; ++n )
	{
		m_pVertexList[ n ].position = VECTOR(0,0,0);
		m_pVertexList[ n ].normal   = VECTOR(0,0,0);
	}

	Graphics *pGraphics = g_pGame->graphics();
	m_pVertexBuffer = pGraphics->CreateVertexBuffer( m_pVertexList,
													 m_nVertices );


	short L1[ 8 ] = { 0, 1, 2, 3, 6, 7, 4, 5 };
	short L2[ 8 ] = { 2, 6, 0, 4, 1, 5, 3, 7 };

	m_ppIndexBuffers = new IDirect3DIndexBuffer9*[ 2 ];
	m_ppIndexBuffers[ 0 ] = pGraphics->CreateIndexBuffer( L1, 8 );
	m_ppIndexBuffers[ 1 ] = pGraphics->CreateIndexBuffer( L2, 8 );


	ZeroMemory( &m_material, sizeof( D3DMATERIAL9 ) );
	m_material.Diffuse.r  = 1.0f;
	m_material.Diffuse.g  = 0.0f;
	m_material.Diffuse.b  = 0.0f;
	m_material.Diffuse.a  = 1.0f;
	m_material.Emissive.r = 0.5f;
	m_material.Emissive.g = 0.0f;
	m_material.Emissive.b = 0.0f;
	m_material.Emissive.a = 1.0f;
}


Block :: ~Block()
{}


void Block :: update()
{
	addForce( m_mass * g_pGame->world()->gravity() );

	RigidSystem :: update();
}


void Block :: render()
{
	RigidSystem :: render();
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
	pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP, 0, 0, 8, 0, 6 );

	pDevice->SetIndices( m_ppIndexBuffers[ 1 ] );
	pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP, 0, 0, 8, 0, 6 );
*/

}
