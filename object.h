#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "definitions.h"

class Space;
class Binding;


class Object
{
	public:
		//------------------------------------------------------------
		// Construction, destruction
		//------------------------------------------------------------
				 Object();
		virtual ~Object();

		//------------------------------------------------------------
		// Properties
		//------------------------------------------------------------
		virtual float   mass       ();
		virtual float   inertia    ( VECTOR &A );
		virtual float   inertia    ( VECTOR &A, VECTOR &P );

		virtual VECTOR  Pos        ();
		virtual VECTOR  Pos_1      ();
		virtual VECTOR  Pos_2      ();
		virtual VECTOR  Velo       ();
		virtual VECTOR  Force      ();

		virtual Space*  pSpace     ();
		virtual VECTOR  I          ();
		virtual VECTOR  J          ();
		virtual VECTOR  K          ();
		virtual VECTOR  Omega      ();
		virtual VECTOR  Torque     ();

		virtual VECTOR* pRotAxis   ();
		virtual VECTOR* pA         ();

		virtual int     children   ();
		virtual Object* child      ( int i );
				Object* parent     ();
				Object* top        ();

		virtual VECTOR  MostCollidedPoint();

		//------------------------------------------------------------
		// Methods
		//------------------------------------------------------------
		virtual void init       ();

		virtual void setMass    ( float   m );
		virtual void setInertia ( float   i );

		virtual void setPos     ( VECTOR &P );
		virtual void setPos_1   ( VECTOR &P );
		virtual void setVelo    ( VECTOR &V );
		virtual void setForce   ( VECTOR &F );

		virtual void addVelo    ( VECTOR &V );
		virtual void addOmega   ( VECTOR &W );

		virtual void setOmega   ( VECTOR &W );
		virtual void setSpace   ( Space *pSpace );
		virtual void setTorque  ( VECTOR &T );

		virtual void setRotAxis ( VECTOR *pV );

		virtual void addForce   ( VECTOR &F );
		virtual void addTorque  ( VECTOR &T );
		virtual void addTorque  ( VECTOR &T, VECTOR &P );

		virtual void move       ( VECTOR &V );
		virtual void spin       ( VECTOR &W );
		virtual void rotate     ( VECTOR &W, VECTOR &P );

		virtual void update     ();
		virtual void update_trans ();
		virtual void update_rot ();
		virtual void render     ();

				void setParent  ( Object *pObject );
		virtual	void setTop     ( Object *pObject );

				void addBinding ( Binding *pBinding );

	protected:
		Object *m_pParent;
		Object *m_pTop;

		Binding **m_ppBindings;
		int       m_nrBindings;
};

#endif
