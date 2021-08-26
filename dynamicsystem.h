#ifndef __DYNAMICSYSTEM_H__
#define __DYNAMICSYSTEM_H__

#include "definitions.h"
#include "ObjectSystem.h"
#include "Atom.h"
#include "Space.h"


class DynamicSystem : public ObjectSystem
{
	public:
		//------------------------------------------------------------
		// Construction, destruction
		//------------------------------------------------------------
				 DynamicSystem( VECTOR &Pos );
		virtual ~DynamicSystem();

		//------------------------------------------------------------
		// Properties
		//------------------------------------------------------------

		//------------------------------------------------------------
		// Methods
		//------------------------------------------------------------
				void addForce  ( VECTOR &F );
				void addTorque ( VECTOR &T );
				void addTorque ( VECTOR &T, VECTOR &P );
		virtual void update();
		virtual void render();

	protected:
		Object **m_ppAtoms;
		int      m_nrAtoms;
		float    m_k;
};

#endif