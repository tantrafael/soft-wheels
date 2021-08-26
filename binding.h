#ifndef __BINDING_H__
#define __BINDING_H__

#include "Object.h"

class Binding
{
	public:
		//------------------------------------------------------------
		// Constructors, destructors
		//------------------------------------------------------------
				 Binding();
				 Binding( Object *p1, Object *p2, float k );
		virtual ~Binding();

		VECTOR Force( Object *pObject );

		//------------------------------------------------------------
		// Methods
		//------------------------------------------------------------
		void setParent( Object *pObject );
		void update();
		void render();

	protected:
		Object *m_pParent;
		Object *m_p1, *m_p2;
		VECTOR  m_R12, m_R21;
		float   m_r0;
		float   m_k;

		void    m_update( Object *p1, Object *p2, VECTOR &R12 );
};


#endif