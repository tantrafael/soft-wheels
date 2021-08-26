#ifndef __BINDINGSYSTEM_H__
#define __BINDINGSYSTEM_H__

#include "definitions.h"
#include "ObjectSystem.h"
#include "Atom.h"
#include "Binding.h"
#include "Space.h"


class BindingSystem : public ObjectSystem
{
	public:
		//------------------------------------------------------------
		// Construction, destruction
		//------------------------------------------------------------
				 BindingSystem( VECTOR &Pos );
		virtual ~BindingSystem();

		//------------------------------------------------------------
		// Properties
		//------------------------------------------------------------

		//------------------------------------------------------------
		// Methods
		//------------------------------------------------------------
				void Bind( Object *pObject1, Object *pObject2, float k );
		virtual void update();
		virtual void render();

	protected:
		Binding **m_ppInternalBindings;
		int       m_nrInternalBindings;
};

#endif