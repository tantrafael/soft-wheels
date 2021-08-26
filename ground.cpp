#include "Ground.h"
#include "Game.h"

extern Game *g_pGame;

using namespace std;


//-----------------------------------------------------------------------------
// Construction, destruction
//-----------------------------------------------------------------------------
Ground :: Ground()
{
	// Load height map
	string filename = "images/heightmap.bmp";

	HDC     hdc;
	HBITMAP hbmp;
	BITMAP  bmp;

	hdc  = CreateCompatibleDC( NULL );
	hbmp = (HBITMAP) LoadImage( NULL, filename.c_str(),
								IMAGE_BITMAP, 0, 0,
								LR_LOADFROMFILE );

	GetObject( hbmp, sizeof( BITMAP ), &bmp );
	SelectObject( hdc, hbmp );

	m_nGridRows       = bmp.bmHeight - ( 1 - ( bmp.bmHeight % 2 ) );
	m_nGridCols       = bmp.bmWidth  - ( 1 - ( bmp.bmWidth  % 2 ) );
	m_nGridPoints     = m_nGridRows * m_nGridCols;
	m_fGridUnitLength = 1.0f;
	m_fGridWidth      = m_nGridRows * m_fGridUnitLength;
	m_fGridHeight     = m_nGridCols * m_fGridUnitLength;


	Graphics         *pGraphics = g_pGame->graphics();
	IDirect3DDevice9 *pDevice   = pGraphics->Device();
	int i;

	//-------------------------------------------------------------------------
	// Create vertices
	m_pGridPoints = new VECTOR[ m_nGridPoints ];
	m_pVertexList = new vertex[ m_nGridPoints ];

	COLORREF  icolor;
	D3DCOLOR  scolor;
	BYTE *pBytes;
	int R, G, B;

	i = 0;
	for( int row = 0; row < m_nGridRows; ++row )
	{
		for( int col = 0; col < m_nGridCols; ++col )
		{
			icolor = GetPixel( hdc, col, row );
			pBytes = (BYTE *) &icolor;
			R = (int) pBytes[0];
			G = (int) pBytes[1];
			B = (int) pBytes[2];
			scolor = D3DCOLOR_XRGB( R, G, B );

			float x =  col * m_fGridUnitLength - 0.5f * m_fGridWidth;
			float y = -row * m_fGridUnitLength + 0.5f * m_fGridHeight;
			float r =  sqrtf( x * x + y * y );
			float z =  0.025f * m_fGridUnitLength * ( R + G + B );

			vertex v;
			v.position.x = x;
			v.position.z = y;
			v.position.y = z;
			v.normal = VECTOR(0,0,0);
		//	v.color  = D3DCOLOR_XRGB( R, G, B );
		//	v.color  = D3DCOLOR_XRGB( 255, 200, 100 );

			m_pGridPoints[ i ] = VECTOR( x, y, z );
			m_pVertexList[ i ] = v;
			++i;
		}
	}

	DeleteObject( hbmp );
	DeleteDC( hdc );


	// Set normals
	for( int row = 0; row < m_nGridRows - 1; ++row )
	{
		for( int col = 0; col < m_nGridCols - 1; ++col )
		{
			int    i0, i1, i2;
			vertex v0, v1, v2;
			VECTOR v0v1, v0v2, N, n;

			// First triangle
			i0 =   row       * m_nGridCols +   col       ;
			i1 = ( row + 1 ) * m_nGridCols +   col       ;
			i2 =   row       * m_nGridCols + ( col + 1 ) ;

			v0 = m_pVertexList[ i0 ];
			v1 = m_pVertexList[ i1 ];
			v2 = m_pVertexList[ i2 ];

			v0v1 = v1.position - v0.position;
			v0v2 = v2.position - v0.position;
			D3DXVec3Cross( &N, &v0v1, &v0v2 );
			D3DXVec3Normalize( &n, &N );

			m_pVertexList[ i0 ].normal -= n;
			m_pVertexList[ i1 ].normal -= n;
			m_pVertexList[ i2 ].normal -= n;

			// Second triangle
			i0 =   row       * m_nGridCols + ( col + 1 );
			i1 = ( row + 1 ) * m_nGridCols +   col      ;
			i2 = ( row + 1 ) * m_nGridCols + ( col + 1 );

			v0 = m_pVertexList[ i0 ];
			v1 = m_pVertexList[ i1 ];
			v2 = m_pVertexList[ i2 ];

			v0v1 = v1.position - v0.position;
			v0v2 = v2.position - v0.position;
			D3DXVec3Cross( &N, &v0v1, &v0v2 );
			D3DXVec3Normalize( &n, &N );

			m_pVertexList[ i0 ].normal -= n;
			m_pVertexList[ i1 ].normal -= n;
			m_pVertexList[ i2 ].normal -= n;
		}
	}

	// Normalize normals
	for( int n = 0; n < m_nGridPoints; ++n )
	{
		VECTOR N = m_pVertexList[ n ].normal;
		D3DXVec3Normalize( &N, &N );
		m_pVertexList[ n ].normal = N;
	}

	m_pVertexBuffer = pGraphics->CreateVertexBuffer( m_pVertexList,
													 m_nGridPoints );
//	delete [] m_pVertexList;


	//-------------------------------------------------------------------------
	// Create indices
	int    nIndices   = 2 * m_nGridCols;
	short *pIndexList = new short[ nIndices ];
	
	i = 0;
	for( int col = 0; col < m_nGridCols; ++col )
	{
		pIndexList[ i ] = col;               ++i;
		pIndexList[ i ] = col + m_nGridCols; ++i;
	}

	m_pIndexBuffer = pGraphics->CreateIndexBuffer( pIndexList,
												   nIndices );
	delete [] pIndexList;


	// Set material
	//-------------------------------------------------------------------------
	ZeroMemory( &m_material, sizeof( D3DMATERIAL9 ) );
	m_material.Diffuse.r = m_material.Ambient.r = 0.00f;
	m_material.Diffuse.g = m_material.Ambient.g = 0.78f;
	m_material.Diffuse.b = m_material.Ambient.b = 0.39f;
	m_material.Diffuse.a = m_material.Ambient.a = 1.0f;
}

Ground :: ~Ground()
{
	m_pIndexBuffer  -> Release();
	m_pVertexBuffer -> Release();
}


//-----------------------------------------------------------------------------
// Methods
//-----------------------------------------------------------------------------
VECTOR Ground :: GridPoint( int nx, int ny )
{
	return m_pGridPoints[ ( m_nGridPoints - 1 ) / 2
						  - ny * m_nGridCols + nx ];
}


//-----------------------------------------------------------------------------
float Ground :: height( float x, float y )
{
	int nx = (int) floorf( x / m_fGridUnitLength );
	int ny = (int) floorf( y / m_fGridUnitLength );
	float x0 = nx * m_fGridUnitLength;
	float y0 = ny * m_fGridUnitLength;
	float x1 = x0 + m_fGridUnitLength;
	float y1 = y0 + m_fGridUnitLength;
	float dx = x - x0;
	float dy = y - y0;

	VECTOR p, vx, vy;
	VECTOR p00 = GridPoint( nx, ny );
	VECTOR p01 = GridPoint( nx, ny + 1 );
	VECTOR p10 = GridPoint( nx + 1, ny );
	VECTOR p11 = GridPoint( nx + 1, ny + 1 );

	if( dx < dy )
	{
		vx = p11 - p01;
		vy = p00 - p01;
		p  = p00 + ( x - x0 ) * vx
				 + ( y - y1 ) * vy;
	}
	else
	{
		vx = p00 - p10;
		vy = p11 - p10;
		p  = p10 + ( x - x1 ) * vx
				 + ( y - y0 ) * vy;
	}

	return p.z;
}


//-----------------------------------------------------------------------------
void Ground :: render()
{
	IDirect3DDevice9 *pDevice = g_pGame->graphics()->Device();
	pDevice->SetStreamSource ( 0, m_pVertexBuffer, 0, vertexSize );
	pDevice->SetIndices      ( m_pIndexBuffer );
	pDevice->SetMaterial     ( &m_material );

	int nVertices  = 2 * m_nGridCols;
	int nTriangles = nVertices - 2;

	for( int row = 0; row < m_nGridRows - 1; ++row )
	{
		pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP,
									   row * m_nGridCols,
									   0,
									   nVertices,
									   0,
									   nTriangles );
	}

/*
	for( int n = 0; n < m_nGridPoints; ++n )
	{
		vertex v  = m_pVertexList[ n ];
		VECTOR p0 = v.position;
		VECTOR p1 = v.position + v.normal;

		vertex VertexList[ 2 ];
		VertexList[ 0 ].position = p0;
		VertexList[ 1 ].position = p1;
	//	VertexList[ 0 ].color = 0xFF0000;
	//	VertexList[ 1 ].color = 0xFF0000;
		pDevice->DrawPrimitiveUP( D3DPT_LINELIST, 1, &VertexList[0], vertexSize );
	}
*/

}
