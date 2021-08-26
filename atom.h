#ifndef __ATOM_H__
#define __ATOM_H__

#include "definitions.h"
#include "Mass.h"
#include "Body.h"


//class Atom : public Body
class Atom : public Mass
{
	public:
		//------------------------------------------------------------
		// Construction, destruction
		//------------------------------------------------------------
				 Atom( VECTOR &pos, float mass );
		virtual ~Atom();

		//------------------------------------------------------------
		// Properties
		//------------------------------------------------------------
				float  inertia( VECTOR &A );
				VECTOR Force();
				VECTOR MostCollidedPoint();

		//------------------------------------------------------------
		// Methods
		//------------------------------------------------------------
				void update();
				void render();

	protected:
		float m_k;
		float m_inertia;
};

#endif