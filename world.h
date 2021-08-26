#ifndef __WORLD_H__
#define __WORLD_H__

#include "definitions.h"
#include "Car.h"
#include "Block.h"
#include "Ball.h"
#include "Wheel.h"
#include "WheelAxis.h"
#include "Ground.h"
#include "Camera.h"
#include "Binding.h"


class World
{
	public:
		//------------------------------------------------------------
		// Construction, destruction
		//------------------------------------------------------------
		 World();
		~World();

		//------------------------------------------------------------
		// Properties
		//------------------------------------------------------------
		VECTOR   gravity   ();
		D3DCOLOR SkyColor  ();
		Car*     car       ();
		Ground*  ground    ();
		Camera*  camera    ();
		float    timeconst ();
		float    dt        ();
		float    dt2       ();

		//------------------------------------------------------------
		// Methods
		//------------------------------------------------------------
		void addObject ( Object *pObject );
		void addBinding( Object *pObject1, Object *pObject2, float k );
		void addAtom   ( Mass   *pAtom   );
		void update    ();
		void render    ();


		Body      *m_pBody;
		Wheel     *m_pWheel;
		WheelAxis *m_pWheelAxis;
		Block     *m_pBlock;
		Ball      *m_pBall;


	protected:
		float      m_timeconst;
		float      m_t, m_t_1, m_t_2;
		float      m_dt, m_dt2;

		VECTOR     m_gravity;
		D3DCOLOR   m_SkyColor;

		int        m_nrChildren;
		Object   **m_ppChildren;

		int        m_nrBindings;
		Binding  **m_ppBindings;

		int        m_nrAtoms;
		Mass     **m_ppAtoms;

		Ground    *m_pGround;
		Car       *m_pCar;
		Camera    *m_pCamera;

		D3DLIGHT9 m_light;
};

#endif