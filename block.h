#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "definitions.h"
#include "RigidSystem.h"
#include "BindingSystem.h"


class Block : public RigidSystem
//class Block : public BindingSystem
{
	public:
		Block( VECTOR &Pos,
			   float  width,
			   float  length,
			   float  height,
			   float  mass );

	   ~Block();

		void update();
		void render();

	protected:
		int     m_nVertices;
		vertex *m_pVertexList;
		IDirect3DVertexBuffer9 *m_pVertexBuffer;
		IDirect3DIndexBuffer9 **m_ppIndexBuffers;

		D3DMATERIAL9 m_material;
};

#endif