#ifndef __OBJECTSYSTEM_H__
#define __OBJECTSYSTEM_H__

#include "definitions.h"
#include "Body.h"


class ObjectSystem : public Body
{
	public:
		//------------------------------------------------------------
		// Construction, destruction
		//------------------------------------------------------------
				 ObjectSystem();
				 ObjectSystem( VECTOR &Pos );
		virtual ~ObjectSystem();

		//------------------------------------------------------------
		// Properties
		//------------------------------------------------------------
				VECTOR  masscenter ();
				float   inertia    ( VECTOR &A );
				float   inertia    ( VECTOR &A, VECTOR &P );

				int     children   ();
				Object* child      ( int i );

		//------------------------------------------------------------
		// Methods
		//------------------------------------------------------------
				void addObject ( Object *pObject );
				void addObject ( Object *pObject, VECTOR &FreedomAxis );
				void setTop    ( Object *pObject );
				void define    ();
				void addForce  ( VECTOR &F );
				void addTorque ( VECTOR &T );
				void addTorque ( VECTOR &T, VECTOR &P );
				void move      ( VECTOR &V );
		virtual void setPos    ( VECTOR &P );
				void rotate    ( VECTOR &P, VECTOR &W );
		virtual void update    ();
		virtual	void render    ();

	protected:
		int      m_nrChildren;
		Object **m_ppChildren;
		VECTOR  *m_pR0;

		int     *m_pDegreesOfFreedom;
		VECTOR  *m_pFreedomAxis;
		PLANE   *m_pFreedomPlane;
};

#endif