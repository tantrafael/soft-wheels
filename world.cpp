#include "World.h"
#include "Game.h"

extern Game *g_pGame;


//-----------------------------------------------------------------------------
// Construction, destruction
//-----------------------------------------------------------------------------
World :: World()
{
	m_timeconst = 1.25f;

	m_t   = m_timeconst * 0.001f * timeGetTime();
	m_t_1 = 0.0f;
	m_t_2 = 0.0f;
	m_dt  = 0.0f;
	m_dt2 = 0.0f;

//	m_gravity   = D3DXVECTOR3( 0, 0, -0.00982f );
//	m_gravity   = D3DXVECTOR3( 0, 0, -2.0f );
	m_gravity   = D3DXVECTOR3( 0, 0, -9.82f );
	m_SkyColor  = D3DCOLOR_XRGB( 150, 200, 255 );

	m_nrChildren = 0;
	m_ppChildren = new Object*  [ 1000 ];

	m_nrBindings = 0;
	m_ppBindings = new Binding* [ 1000 ];

	m_nrAtoms    = 0;
	m_ppAtoms    = new Mass*    [ 1000 ];


	m_pGround = new Ground();
//	addObject( m_pGround );

//	addObject( new Atom( VECTOR( 0.0f, 0.0f, 2.0f ), 1.0f, 1.0f ) );

	m_pCar = new Car( VECTOR( 0, 0, 2.0f ) );
	addObject( m_pCar );

//	addObject( new Wheel( VECTOR(0,0,1.0f), 25.0f, 0.5f ) );

//	Object *pBlock = new Block( VECTOR(0,0,2.0f), 1.0f, 1.0f, 1.0f, 8.0f );
//	addObject( pBlock );
//	pBlock->spin( VECTOR(0,0.1f,0.1f) );


	m_pCamera = new Camera( VECTOR( -5.0f, -10.0f, 0.0f ), 25.0f );
	m_pCamera->spin( VECTOR( 0.0f, 0.0f,-0.5f ) );
	addObject( m_pCamera );


	ZeroMemory( &m_light, sizeof( D3DLIGHT9 ) );
	m_light.Type      = D3DLIGHT_DIRECTIONAL;
	m_light.Diffuse.r = 1.0f;
	m_light.Diffuse.g = 1.0f;
	m_light.Diffuse.b = 1.0f;
//	m_light.Position  = VECTOR(0,0,0);
	m_light.Direction = VECTOR( 0.5f, -1.0f, 0.5f );
	m_light.Range     = 1000.0f;
	g_pGame->graphics()->Device()->SetLight( 0, &m_light );
	g_pGame->graphics()->Device()->LightEnable( 0, TRUE );
}


World :: ~World() {}


//-----------------------------------------------------------------------------
// Properties
//-----------------------------------------------------------------------------
VECTOR   World :: gravity   () { return m_gravity;    }
D3DCOLOR World :: SkyColor  () { return m_SkyColor;   }
Camera*  World :: camera    () { return m_pCamera;    }
Car*     World :: car       () { return m_pCar;       }
Ground*  World :: ground    () { return m_pGround;    }
float    World :: timeconst () { return m_timeconst;  }
float    World :: dt        () { return m_dt;         }
float    World :: dt2       () { return m_dt2;        }

//-----------------------------------------------------------------------------
// Public functions
//-----------------------------------------------------------------------------
void World :: addObject( Object *pObject )
{
	m_ppChildren[ m_nrChildren ] = pObject;
	m_nrChildren++;
}


//-----------------------------------------------------------------------------
void World :: addBinding( Object *pObject1, Object *pObject2, float k )
{
	m_ppBindings[ m_nrBindings ] = new Binding( pObject1, pObject2, k );
	m_nrBindings++;
}


//-----------------------------------------------------------------------------
void World :: addAtom( Mass *pAtom )
{
	m_ppAtoms[ m_nrAtoms ] = pAtom;
	m_nrAtoms++;
}


//-----------------------------------------------------------------------------
void World :: update()
{
	float t = 0.001f * timeGetTime();

	m_t_2 = m_t_1;
	m_t_1 = m_t;
	m_t   = m_timeconst * t;
//	m_t   = m_t + 0.025f;
	m_dt  = m_t - m_t_1;
	m_dt2 = m_dt * m_dt;

	for( int i = 0; i < m_nrChildren; ++i )
	{
		Object *pChild_i = m_ppChildren[ i ];

	//	pChild_i->addForce( pChild_i->mass() * m_gravity );
		pChild_i->update();
	}
}


//-----------------------------------------------------------------------------
void World :: render()
{
//	g_pGame->graphics()->Device()->SetLight( 0, &m_light );

	g_pGame->graphics()->Begin();

	m_pGround->render();

	for( int n = 0; n < m_nrChildren; ++n )
	{
		m_ppChildren[ n ]->render();
	}

	g_pGame->graphics()->End();
}
