#ifndef __MASS_H__
#define __MASS_H__

#include "definitions.h"
#include "Object.h"


class Mass : public Object
{
	public:
		//------------------------------------------------------------
		// Construction, destruction
		//------------------------------------------------------------
				 Mass();
				 Mass( VECTOR &pos, float mass );
		virtual ~Mass();

		//------------------------------------------------------------
		// Properties
		//------------------------------------------------------------
				float  mass    ();
				float  inertia ( VECTOR &A, VECTOR &P );
		virtual VECTOR Pos     ();
				VECTOR Pos_1   ();
				VECTOR Velo    ();
				VECTOR Force   ();

				float  t       ();
				float  t_1     ();
				float  t_2     ();

		//------------------------------------------------------------
		// Methods
		//------------------------------------------------------------
		virtual	void init     ();

				void setMass      ( float   m );
		virtual	void setPos       ( VECTOR &P );
		virtual	void setPos_1     ( VECTOR &P );
				void setVelo      ( VECTOR &V );
				void setForce     ( VECTOR &F );
				void addVelo      ( VECTOR &V );
				void addForce     ( VECTOR &F );
		virtual void move         ( VECTOR &V );
		virtual void rotate       ( VECTOR &W, VECTOR &P );
				void update_trans ();
		virtual void update       ();

	protected:
		float  m_mass;
		VECTOR m_Force;
		VECTOR m_Pos, m_Pos_1;
		VECTOR m_Acc;
		VECTOR m_Velo;
		float  m_t, m_t_1;
};

#endif
