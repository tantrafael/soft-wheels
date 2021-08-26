#include "Graphics.h"
#include "Game.h"

extern Game *g_pGame;


//-----------------------------------------------------------------------------
// Construction, destruction
//-----------------------------------------------------------------------------
Graphics :: Graphics()
{
	m_InitD3D();

	m_pD3Ddevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
						 0xDDDDDD, 1.0f, 0 );

	m_pD3Ddevice->Present( NULL, NULL, NULL, NULL );
}

Graphics :: ~Graphics()
{
	m_TermD3D();
}


//-----------------------------------------------------------------------------
// Properties
//-----------------------------------------------------------------------------
IDirect3DDevice9* Graphics :: Device()
{
	return m_pD3Ddevice;
}


//-----------------------------------------------------------------------------
// Methods
//-----------------------------------------------------------------------------
IDirect3DVertexBuffer9* Graphics :: CreateVertexBuffer( vertex *pVertexList,
														int     nVertices )
{
	IDirect3DVertexBuffer9 *pVertexBuffer;

	int memsize = nVertices * sizeof( vertex );
	m_pD3Ddevice->CreateVertexBuffer( memsize, D3DUSAGE_WRITEONLY,
									  vertexFVF, D3DPOOL_DEFAULT,
									  &pVertexBuffer, NULL );
	void* pVertices;
	pVertexBuffer->Lock( 0, memsize, (void**) &pVertices, 0 );
	memcpy( pVertices, pVertexList, memsize );
	pVertexBuffer->Unlock();

	return pVertexBuffer;
}


//-----------------------------------------------------------------------------
IDirect3DIndexBuffer9* Graphics :: CreateIndexBuffer( short *pIndexList,
													  int    nIndices  )
{
	IDirect3DIndexBuffer9 *pIndexBuffer;

	int memsize = nIndices * sizeof( short );
	m_pD3Ddevice->CreateIndexBuffer( memsize, D3DUSAGE_WRITEONLY,
								D3DFMT_INDEX16, D3DPOOL_DEFAULT,
								&pIndexBuffer, NULL );

	void* pIndices;
	pIndexBuffer->Lock( 0, memsize, (void**) &pIndices, 0 );
	memcpy( pIndices, pIndexList, memsize );
	pIndexBuffer->Unlock();

	return pIndexBuffer;
}

//-----------------------------------------------------------------------------
void Graphics :: Point( VECTOR &P )
{
	vertex VertexList [ 1 ];
	VECTOR PointList  [ 1 ];
	PointList[ 0 ] = P;

	VECTOR Pos = PointList[ 0 ];
	VertexList[ 0 ].position.x = Pos.x;
	VertexList[ 0 ].position.z = Pos.y;
	VertexList[ 0 ].position.y = Pos.z;
	VertexList[ 0 ].normal = VECTOR( 0.0f, 0.0f, 0.0f);
//	VertexList[ 0 ].color = 0xFF0000;

	m_pD3Ddevice->DrawPrimitiveUP( D3DPT_POINTLIST, 1,
								   &VertexList[0], vertexSize );
}


//-----------------------------------------------------------------------------
void Graphics :: Line( VECTOR &P1, VECTOR &P2 )
{
	vertex VertexList [ 2 ];
	VECTOR PointList  [ 2 ];
	PointList[ 0 ] = P1;
	PointList[ 1 ] = P2;

	for( int n = 0; n < 2; ++n )
	{
		VECTOR Pos = PointList[ n ];
		VertexList[ n ].position.x = Pos.x;
		VertexList[ n ].position.z = Pos.y;
		VertexList[ n ].position.y = Pos.z;
		VertexList[ n ].normal = VECTOR( 0.0f, 0.0f, 0.0f);
	//	VertexList[ n ].color = 0xFF0000;
	}

	m_pD3Ddevice->DrawPrimitiveUP( D3DPT_LINELIST, 1,
								   &VertexList[0], vertexSize );
}


//-----------------------------------------------------------------------------
void Graphics :: Triangle( VECTOR &P1, VECTOR &P2, VECTOR &P3, long color )
{
	vertex VertexList [ 3 ];
	VECTOR PointList  [ 3 ];
	PointList[ 0 ] = P1;
	PointList[ 1 ] = P2;
	PointList[ 2 ] = P3;

	for( int n = 0; n < 3; ++n )
	{
		VECTOR Pos = PointList[ n ];
		VertexList[ n ].position.x = Pos.x;
		VertexList[ n ].position.y = Pos.z;
		VertexList[ n ].position.z = Pos.y;
	}

	m_pD3Ddevice->DrawPrimitiveUP( D3DPT_TRIANGLELIST, 1,
								   &VertexList[0], vertexSize );
}


//-----------------------------------------------------------------------------
void Graphics :: Begin()
{
	D3DCOLOR bgColor = g_pGame->world()->SkyColor();
	m_pD3Ddevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
						 bgColor, 1.0f, 0 );

	m_pD3Ddevice->BeginScene();

	Camera *pCamera = g_pGame->world()->camera();

	VECTOR P = pCamera->Pos();
	VECTOR I = pCamera->I();
	VECTOR J = pCamera->J();
	VECTOR K = pCamera->K();

	D3DXMATRIX A( I.x,  I.z,  I.y,  0.0f,
				  K.x,  K.z,  K.y,  0.0f,
				  J.x,  J.z,  J.y,  0.0f,
				  P.x,  P.z,  P.y,  1.0f );

	D3DXMATRIX A_inv;
	D3DXMatrixInverse( &A_inv, NULL, &A );
	
//	D3DXMATRIX view( i.x(),  k.x(),  j.x(),  0.0f,
//					 i.z(),  k.z(),  j.z(),  0.0f,
//					 i.y(),  k.y(),  j.y(),  0.0f,
//					-p.x(), -p.z(), -p.y(),  1.0f );

	m_pD3Ddevice->SetTransform( D3DTS_VIEW, &A_inv );
}


//-----------------------------------------------------------------------------
void Graphics :: End()
{
	m_pD3Ddevice->EndScene();
	m_pD3Ddevice->Present( NULL, NULL, NULL, NULL );
}


//-----------------------------------------------------------------------------
// Protected methods
//-----------------------------------------------------------------------------
HRESULT Graphics :: m_InitD3D()
{
	HRESULT hr;
	
	// Create D3D object
	m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
	if( !m_pD3D ) return E_FAIL;

	// Get current desktop display mode
	D3DDISPLAYMODE d3ddm;
	hr = m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm );
	if( FAILED(hr) ) return E_FAIL;

	// Set parameters
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof(d3dpp) );

	d3dpp.BackBufferWidth        = g_pGame->window()->cols();
	d3dpp.BackBufferHeight       = g_pGame->window()->rows();
	d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow          = g_pGame->window()->hWnd();
	d3dpp.Windowed               = TRUE;
	d3dpp.BackBufferFormat       = d3ddm.Format;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// Create D3D device
	hr = m_pD3D->CreateDevice( D3DADAPTER_DEFAULT,
							   D3DDEVTYPE_HAL,
							   g_pGame->window()->hWnd(),
						//	   D3DCREATE_HARDWARE_VERTEXPROCESSING,
							   D3DCREATE_SOFTWARE_VERTEXPROCESSING,
							   &d3dpp,
							   &m_pD3Ddevice );

	if( FAILED(hr) ) return E_FAIL;

	float s = 3.0f;
	DWORD PointSize = *( (DWORD*) &s );

	// Set render states
 	m_pD3Ddevice->SetRenderState( D3DRS_ZENABLE,  TRUE          );
	m_pD3Ddevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
//	m_pD3Ddevice->SetRenderState( D3DRS_POINTSCALEENABLE, TRUE );
	m_pD3Ddevice->SetRenderState( D3DRS_POINTSIZE, PointSize );
	m_pD3Ddevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE  );
	m_pD3Ddevice->SetRenderState( D3DRS_LIGHTING, TRUE          );
	m_pD3Ddevice->SetRenderState( D3DRS_AMBIENT,  0x00202020    );

	// Set matrices
	D3DXMATRIX world, view, proj;

	D3DXMatrixIdentity      ( &world );
	D3DXMatrixIdentity      ( &view  );
	D3DXMatrixPerspectiveLH ( &proj, 1.2f, 1.0f, 2.0f, 10000.0f );

	m_pD3Ddevice->SetTransform( D3DTS_WORLD,      &world );
	m_pD3Ddevice->SetTransform( D3DTS_VIEW,       &view  );
	m_pD3Ddevice->SetTransform( D3DTS_PROJECTION, &proj  );

	// Set vertex format
	m_pD3Ddevice->SetFVF( vertexFVF );

	return S_OK;
}


//-----------------------------------------------------------------------------
void WINAPI Graphics :: m_TermD3D()
{
	if (m_pD3D)
	{
		if (m_pD3Ddevice)
		{
			m_pD3Ddevice->Release();
			m_pD3Ddevice = NULL;
		}
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}
