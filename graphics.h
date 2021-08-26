#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "definitions.h"


class Graphics
{
	public:
		//------------------------------------------------------------
		// Construction, destruction
		//------------------------------------------------------------
		 Graphics();
		~Graphics();

		//------------------------------------------------------------
		// Properties
		//------------------------------------------------------------
		IDirect3DDevice9* Device();

		//------------------------------------------------------------
		// Methods
		//------------------------------------------------------------
		IDirect3DVertexBuffer9* CreateVertexBuffer ( vertex *pVertexList,
													 int     nVertices );

		IDirect3DIndexBuffer9*  CreateIndexBuffer  ( short  *pIndexList,
												     int     nIndices  );

		void Point    ( VECTOR &P );
		void Line     ( VECTOR &P1, VECTOR &P2 );
		void Triangle ( VECTOR &P1, VECTOR &P2, VECTOR &P3, long color );

		void Begin ();
		void End   ();

	private:
		//------------------------------------------------------------
		// Variables
		//------------------------------------------------------------
		IDirect3D9             *m_pD3D;
		IDirect3DDevice9       *m_pD3Ddevice;

		//------------------------------------------------------------
		// Methods
		//------------------------------------------------------------
		     HRESULT m_InitD3D();
		void WINAPI  m_TermD3D();
};

#endif
