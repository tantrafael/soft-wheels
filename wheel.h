#ifndef __WHEEL_H__
#define __WHEEL_H__

#include "definitions.h"
#include "Atom.h"
#include "RigidSystem.h"
#include "DynamicSystem.h"
#include "BindingSystem.h"


//class Wheel : public ObjectSystem
class Wheel : public RigidSystem
//class Wheel : public DynamicSystem
//class Wheel : public BindingSystem
{
	public:
		Wheel( VECTOR &pos, float mass, float r );
	   ~Wheel();

		void update();
		void render();

	protected:
		float m_r1;
		float m_r2;
		float m_width;
		int   m_N;

		ObjectSystem *m_pCylinder1;
		ObjectSystem *m_pCylinder2;

		int     m_nVertices;
		vertex *m_pVertexList;
		IDirect3DVertexBuffer9 *m_pVertexBuffer;
		IDirect3DIndexBuffer9 **m_ppIndexBuffers;

		D3DMATERIAL9 m_material;
};

#endif
