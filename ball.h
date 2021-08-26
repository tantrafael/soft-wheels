#ifndef __BALL_H__
#define __BALL_H__

#include "definitions.h"
#include "Body.h"


class Ball : public Body
{
	public:
		//------------------------------------------------------------
		// Construction, destruction
		//------------------------------------------------------------
				 Ball( VECTOR &pos, float mass, float rad );
		virtual ~Ball();

		//------------------------------------------------------------
		// Properties
		//------------------------------------------------------------
				float inertia( VECTOR &A );
				float inertia( VECTOR &A, VECTOR &P );

		//------------------------------------------------------------
		// Methods
		//------------------------------------------------------------
				void update();
				void render();

	protected:
		float m_inertia;
		float m_rad;
};

#endif