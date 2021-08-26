#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__


//------------------------------------------------------------
// Headers and libraries
//------------------------------------------------------------
#include <windows.h>
#include <mmsystem.h>
#include <string>
#include <math.h>
#include <d3d9.h>
#include <d3dx9math.h>
#pragma comment ( lib, "winmm.lib"   )
#pragma comment ( lib, "d3d9.lib"   )
#pragma comment ( lib, "d3dx9.lib"  )


//------------------------------------------------------------
// Classes
//------------------------------------------------------------


//------------------------------------------------------------
// Type definitions
//------------------------------------------------------------
typedef D3DXVECTOR3 VECTOR;
typedef D3DXMATRIX  MATRIX;


//------------------------------------------------------------
// Structs
//------------------------------------------------------------

struct PLANE
{
	VECTOR P, N;
};

struct vertex
{
	VECTOR   position;
	VECTOR   normal;
//	D3DCOLOR color;
};

struct triangle
{
	vertex v0, v1, v2;
	VECTOR normal;
};

struct indexStrip
{
	short *indexList;
	int    length;
};

//------------------------------------------------------------
// Constants
//------------------------------------------------------------
const float pi = 3.14159265358979323846f;
//const float g_timestep = 0.001f;


const VECTOR zero  = VECTOR( 0, 0, 0 );
const VECTOR origo = VECTOR( 0, 0, 0 );

//const int vertexFVF  = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE;
const int vertexFVF  = D3DFVF_XYZ | D3DFVF_NORMAL;
const int vertexSize = sizeof( vertex );


#endif