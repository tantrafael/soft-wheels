#ifndef __GROUND_H__
#define __GROUND_H__

#include "definitions.h"


class Ground
{
	public:
		Ground();
	   ~Ground();

		VECTOR GridPoint( int nx, int ny );
		float height( float x, float y );

		void render();

	private:
		int     m_nGridRows;
		int     m_nGridCols;
		int     m_nGridPoints;
		float   m_fGridUnitLength;
		float   m_fGridWidth;
		float   m_fGridHeight;

		VECTOR *m_pGridPoints;
		vertex *m_pVertexList;

		IDirect3DVertexBuffer9 *m_pVertexBuffer;
		IDirect3DIndexBuffer9  *m_pIndexBuffer;

		D3DMATERIAL9 m_material;
};

#endif