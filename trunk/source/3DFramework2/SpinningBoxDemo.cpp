/////////////////////////////////////////////////////////////
/// SpinningBoxDemo.cpp
///		Here's the definition for the GameTemplate. 
/// In here is an example of how to inherit from the D3DApp
/// framework correctly and setup functions to update and draw
/// your game / D3D Application.
///
/// There's a define at the top of the header file you can 
/// toggle to see the framework in action!
///
/////////////////////////////////////////////////////////////
#include "SpinningBoxDemo.h"


//===================================================
// GameTemplate
//	Constructor designed to pass all the required 
// data to the base class in order to setup the window
// and d3d stuff.
// 
//===================================================
SpinningBoxDemo::SpinningBoxDemo(HINSTANCE hInstance, std::string title, D3DDEVTYPE devType, DWORD requestedVP)
		: D3DApp(hInstance, title, devType, requestedVP)
{
	// TODO: Initialize here
#ifdef SHOWDEMO
	
	myCamera = new camera(md3dDev);

	D3DXCreateMeshFVF(12, 8, D3DXMESH_MANAGED, D3DFVF_CUSTOMVERTEX, md3dDev, &boxMesh);


	// Create Vertex List
	CUSTOMVERTEX g_Vertices[] = 
	{
		// X Y Z - COLOR
		{ -1.0f, -1.0f, -1.0f, 0.0, 1.0 }, // 0
		{ -1.0f,  1.0f, -1.0f, 0.0, 0.0 }, // 1
		{  1.0f,  1.0f, -1.0f, 1.0, 0.0 }, // 2
		{  1.0f, -1.0f, -1.0f, 1.0, 1.0 }, // 3

		{ -1.0f, -1.0f,  1.0f, 0.0, 0.0 }, // 4
		{  1.0f, -1.0f,  1.0f, 1.0, 0.0 }, // 5
		{  1.0f,  1.0f,  1.0f, 1.0, 1.0 }, // 6
		{ -1.0f,  1.0f,  1.0f, 0.0, 1.0 }, // 7
	};
	// Create Index List
	WORD IndexData[] = {
		0,1,2,
		2,3,0,
		4,5,6,
		6,7,4,
		0,3,5,
		5,4,0,
		3,2,6,
		6,5,3,
		2,1,7,
		7,6,2,
		1,0,4,
		4,7,1
	};
	
	// prepare to copy the vertices into the vertex buffer
	VOID* pVertices;

	if FAILED(boxMesh->LockVertexBuffer(D3DLOCK_DISCARD, (void**)&pVertices))
	{
		MessageBox(0, "Could not lock vertex buffer", "Error", MB_OK);
		PostQuitMessage(0);
	}
	memcpy(pVertices, g_Vertices, sizeof(g_Vertices));
	boxMesh->UnlockVertexBuffer();

	// prepare to copy the indexes into the index buffer
	VOID* IndexPtr;
	if FAILED(boxMesh->LockIndexBuffer(0, &IndexPtr))
	{
		MessageBox(0, "Could not lock index buffer", "Error", MB_OK);
		PostQuitMessage(0);
	}
	memcpy(IndexPtr, IndexData, sizeof(IndexData)*sizeof(WORD));
	boxMesh->UnlockIndexBuffer();

	// Setup Texture
	if FAILED( D3DXCreateTextureFromFile(md3dDev, "test.jpg", &g_pTexture))
	{
		MessageBox(0, "Failed to load Texture From File \"test.jpg\".", "Error", MB_OK);
		PostQuitMessage(0);
	};

	zPosition = 1.0f;

	xRotation = 0.0f;
	yRotation = 0.0f;
	zRotation = 0.0f;
#endif
}

//===================================================
// updateScene
//	Any updating of game logic goes here. 
// 
//===================================================
void SpinningBoxDemo::updateScene(float elapsed)
{
	// TODO: Update Code Here

}

//===================================================
// drawScene
//	When you want to draw; do it here. 
// 
//===================================================
void SpinningBoxDemo::drawScene()
{
	// TODO: Draw Code Here
	md3dDev->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);
#ifdef SHOWDEMO
	md3dDev->BeginScene();
	
	// Camera Setup
	myCamera->CreateCamera(0.1f, 50.0f);
	myCamera->moveCamera(D3DXVECTOR3(0.0f, 0.0f, -3.0f));
	myCamera->pointCamera(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// Set texture
	md3dDev->SetTexture(0, g_pTexture);
	if(zPosition < 35.0f)
	{
		myCamera->Draw(boxMesh, 
					   D3DXVECTOR3(1.0f, 1.0f, 1.0f), 
					   D3DXVECTOR3(xRotation+=0.01f, yRotation, zRotation), 
					   D3DXVECTOR3(0.0f, 0.0f, zPosition+= 0.05f));
	}
	else
	{
		myCamera->Draw(boxMesh, 
				   D3DXVECTOR3(1.0f, 1.0f, 1.0f), 
				   D3DXVECTOR3(xRotation, yRotation, zRotation), 
				   D3DXVECTOR3(0.0f, 0.0f, zPosition));
	}

	md3dDev->EndScene();
#endif
	md3dDev->Present(0, 0, 0, 0);
}

//===================================================
// ~SpinningBoxDemo
//	Destructor. Designed to release any resources
// which were acquired during the course of this app.
// 
//===================================================
SpinningBoxDemo::~SpinningBoxDemo()
{
#ifdef SHOWDEMO
	g_pTexture->Release();
	boxMesh->Release();
#endif
	// TODO: Release all dynamic resources here
}