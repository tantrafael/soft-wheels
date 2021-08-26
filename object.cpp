#include "Object.h"
#include "Space.h"
#include "Binding.h"


//--------------------------------------------------------------------
// Construction, destruction
//--------------------------------------------------------------------
Object :: Object()
{
	m_pParent = NULL;
	m_pTop    = this;

	m_ppBindings = new Binding* [ 100 ];
	m_nrBindings = 0;
}

Object :: ~Object() {}


//--------------------------------------------------------------------
// Properties
//--------------------------------------------------------------------
float   Object :: mass       ()                       { return 1.0f; }
float   Object :: inertia    ( VECTOR &A )            { return 1.0f; }
float   Object :: inertia    ( VECTOR &A, VECTOR &P ) { return 1.0f; }

VECTOR  Object :: Pos        () { return VECTOR(0,0,0); }
VECTOR  Object :: Pos_1      () { return VECTOR(0,0,0); }
VECTOR  Object :: Pos_2      () { return VECTOR(0,0,0); }
VECTOR  Object :: Velo       () { return VECTOR(0,0,0); }
VECTOR  Object :: Force      () { return VECTOR(0,0,0); }

Space*  Object :: pSpace     () { return NULL;          }
VECTOR  Object :: I          () { return VECTOR(0,0,0); }
VECTOR  Object :: J          () { return VECTOR(0,0,0); }
VECTOR  Object :: K          () { return VECTOR(0,0,0); }
VECTOR  Object :: Omega      () { return VECTOR(0,0,0); }
VECTOR  Object :: Torque     () { return VECTOR(0,0,0); }

VECTOR* Object :: pRotAxis   () { return NULL;          }
VECTOR* Object :: pA         () { return NULL;          }

int     Object :: children   () { return 0;             }
Object* Object :: child      ( int i ) { return NULL;   }
Object* Object :: parent     () { return m_pParent;     }
Object* Object :: top        () { return m_pTop;        }

VECTOR  Object :: MostCollidedPoint() { return VECTOR(0,0,0); }

//--------------------------------------------------------------------
// Methods
//--------------------------------------------------------------------
void Object :: init       ()                       {}

void Object :: setMass    ( float   m )            {}
void Object :: setInertia ( float   i )            {}

void Object :: setPos     ( VECTOR &P )            {}
void Object :: setPos_1   ( VECTOR &P )            {}
void Object :: setVelo    ( VECTOR &V )            {}
void Object :: setForce   ( VECTOR &F )            {}

void Object :: addVelo    ( VECTOR &V )            {}
void Object :: addOmega   ( VECTOR &W )            {}

void Object :: setSpace   ( Space *pSpace )        {}
void Object :: setOmega   ( VECTOR &W )            {}
void Object :: setTorque  ( VECTOR &T )            {}

void Object :: setRotAxis ( VECTOR *pV )           {}

void Object :: addForce   ( VECTOR &F )            {}
void Object :: addTorque  ( VECTOR &T )            {}
void Object :: addTorque  ( VECTOR &T, VECTOR &P ) {}

void Object :: move       ( VECTOR &V )            {}
void Object :: spin       ( VECTOR &W )            {}
void Object :: rotate     ( VECTOR &W, VECTOR &P ) {}

void Object :: update     ()                       {}
void Object :: update_trans ()                     {}
void Object :: update_rot ()                       {}
void Object :: render     ()                       {}

void Object :: setParent  ( Object *pObject )
{ 
	m_pParent = pObject;
}

void Object :: setTop     ( Object *pObject )
{ 
	m_pTop = pObject;
}

void Object :: addBinding ( Binding *pBinding )
{ 
	m_ppBindings[ m_nrBindings ] = pBinding;
	m_nrBindings++;
}
