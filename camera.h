#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "definitions.h"
#include "Body.h"
#include "Binding.h"

class Game;


class Camera : public Body
{
	public:
		//------------------------------------------------------------
		// Construction, destruction
		//------------------------------------------------------------
		Camera();
		Camera( VECTOR &Pos, float mass );
	   ~Camera();

		//------------------------------------------------------------
		// Properties
		//------------------------------------------------------------

		//------------------------------------------------------------
		// Methods
		//------------------------------------------------------------
		void update();

	protected:
		float m_d0;
};

#endif