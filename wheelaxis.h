#ifndef __WHEELAXIS_H__
#define __WHEELAXIS_H__

#include "definitions.h"
#include "RigidSystem.h"
#include "DynamicSystem.h"
#include "Wheel.h"
#include "Atom.h"


class WheelAxis : public RigidSystem
{
	public:
			 WheelAxis( VECTOR &Pos );
	virtual ~WheelAxis();

			Wheel* LeftWheel();
			Wheel* RightWheel();

	protected:
		Wheel *m_pW1, *m_pW2;
	//	Atom *m_pW1, *m_pW2;
};

#endif