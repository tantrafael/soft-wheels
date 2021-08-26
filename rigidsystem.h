#ifndef __RIGIDSYSTEM_H__
#define __RIGIDSYSTEM_H__

#include "definitions.h"
#include "ObjectSystem.h"
#include "Atom.h"
#include "Space.h"


class RigidSystem : public ObjectSystem
{
	public:
		//------------------------------------------------------------
		// Construction, destruction
		//------------------------------------------------------------
				 RigidSystem();
				 RigidSystem( VECTOR &Pos );
		virtual ~RigidSystem();

		//------------------------------------------------------------
		// Properties
		//------------------------------------------------------------
		VECTOR  Force();
		VECTOR* pRotAxis();
		VECTOR* pA();
		VECTOR  MostCollidedPoint();

		//------------------------------------------------------------
		// Methods
		//------------------------------------------------------------
				void move( VECTOR &V );
				void setPos( VECTOR &P );
				void setRotAxis( VECTOR *pA, VECTOR *pRotAxis );
		virtual void update();
		virtual void render();

		void PlaceChildren();

	protected:
		Object **m_ppAtoms;
		int      m_nrAtoms;
		float    m_k;
		float    m_e;

		VECTOR  m_CollisionPoint;
		VECTOR  *m_pA, *m_pRotAxis;

		void m_addExternalForces();
		void m_collisionUpdate();
};

#endif