#ifndef __BODY_H__
#define __BODY_H__

#include "definitions.h"
#include "Mass.h"

class Body : public Mass
{
	public:
		//------------------------------------------------------------
		// Construction, destruction
		//------------------------------------------------------------
				 Body();
				 Body( VECTOR &Pos, float mass );
		virtual ~Body();

		//------------------------------------------------------------
		// Properties
		//------------------------------------------------------------
		virtual float  inertia ( VECTOR &A );
				Space* pSpace();
		        VECTOR I();
		        VECTOR J();
		        VECTOR K();
				VECTOR Omega  ();
				VECTOR Torque ();

		//------------------------------------------------------------
		// Methods
		//------------------------------------------------------------
				void setInertia ( float   i );
				void setSpace   ( Space *pSpace );
				void setOmega   ( VECTOR &W );
				void setTorque  ( VECTOR &T );
				void addOmega   ( VECTOR &W );
				void addTorque  ( VECTOR &T );
				void addTorque  ( VECTOR &T, VECTOR &P );
				void forceToAxis  ( VECTOR &A, float f );
				void forceToPlane ( VECTOR &N, float f );
				void spin       ( VECTOR &W );
		virtual	void rotate     ( VECTOR &W, VECTOR &P );
				void update_rot ();
		virtual void update     ();
		virtual void render     ();

	protected:
		float  m_inertia;
		Space *m_pSpace;
		VECTOR m_Torque;
		VECTOR m_Alpha;
		VECTOR m_Omega;
		VECTOR m_RotCenter;
};

#endif
