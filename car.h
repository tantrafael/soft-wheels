#ifndef __CAR_H__
#define __CAR_H__

#include "definitions.h"
#include "RigidSystem.h"
#include "DynamicSystem.h"
#include "BindingSystem.h"
#include "Atom.h"
#include "Block.h"
#include "WheelAxis.h"

class Game;


//class Car : public ObjectSystem
class Car : public RigidSystem
//class Car : public BindingSystem
{
	public:
		//------------------------------------------------------------
		// Construction, destruction
		//------------------------------------------------------------
				 Car( VECTOR &Pos );
		virtual ~Car();

		//------------------------------------------------------------
		// Properties
		//------------------------------------------------------------

		//------------------------------------------------------------
		// Methods
		//------------------------------------------------------------
				void forward ();
				void back    ();
				void left    ();
				void right   ();
				void forceToAxis  ( Object *pObject, VECTOR &A, float k );
				void forceToPlane ( Object *pObject, VECTOR &N, float k );
				void alignToAxis  ( Object *pObject, VECTOR &P, VECTOR &A );
				void update  ();
				void render  ();

	protected:

		Block *m_pChassi;

		WheelAxis *m_pFrontWheels;
		WheelAxis *m_pBackWheels;

		Atom  *m_pA1, *m_pA2, *m_pA3, *m_pA4, *m_pA5, *m_pA6, *m_pA7, *m_pA8;
	//	Atom  *m_pW1, *m_pW2, *m_pW3, *m_pW4;
		Wheel *m_pW1, *m_pW2, *m_pW3, *m_pW4;
		Binding *m_pB1, *m_pB2, *m_pB3, *m_pB4;
		RigidSystem *m_pWheelAxis1;
		RigidSystem *m_pWheelAxis2;
		RigidSystem *m_pWheelSystem;
	//	Wheel *m_pFrontWheels;
		Body  *m_pSteeringWheel;
};

#endif
