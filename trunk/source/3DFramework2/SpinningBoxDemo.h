#ifndef SPINNINGBOX_H
#define SPINNINGBOX_H

#include "D3DApp.h"
#include "Render Pipeline\\camera.h"

#define SHOWDEMO

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_TEX1)

struct CUSTOMVERTEX
{
	FLOAT x, y, z;	// The untransformed, 3D position for the vertex
	float tu, tv;
};


class SpinningBoxDemo : public D3DApp
{
public:
	SpinningBoxDemo(HINSTANCE hInstance, std::string title, D3DDEVTYPE devType, DWORD requestedVP);
	~SpinningBoxDemo();

	void updateScene(float elapsed);
	void drawScene();

private:
	// Whatever private game variables go here
#ifdef SHOWDEMO

		// Camera object
	camera* myCamera;
		// Box
	LPD3DXMESH boxMesh;
		// Box Texture
	LPDIRECT3DTEXTURE9 g_pTexture;

	float zPosition;

	float xRotation;
	float yRotation;
	float zRotation;
#endif


};

#endif