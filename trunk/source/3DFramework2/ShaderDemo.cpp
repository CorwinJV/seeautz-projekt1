#include "ShaderDemo.h"


ShaderDemo::ShaderDemo(HINSTANCE hInstance, std::string title, D3DDEVTYPE devType, DWORD requestedVP)
	: D3DApp(hInstance, title, devType, requestedVP)
{

	if(!checkDeviceCaps())
	{
		MessageBox(0, "Does not support shader version 2.0", NULL, MB_OK);
		PostQuitMessage(0);
	}

	//=======================================
	// Camera Initialization
	//=======================================
	myCamera = new camera(md3dDev);


	//=======================================
	// Geometry Initialization
	//=======================================
	D3DXCreateTeapot(md3dDev, &teapotMesh, NULL);


	//=======================================
	// Vertex Declaration
	//=======================================
	D3DVERTEXELEMENT9 VertexPosElements[] = 
	{
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		D3DDECL_END()
	};
	md3dDev->CreateVertexDeclaration(VertexPosElements, &mVertexDecl);

	yRotation = 0.0f;
}


ShaderDemo::~ShaderDemo()
{
	delete myCamera;
	mVertexDecl->Release();	
	teapotMesh->Release();
}

bool ShaderDemo::checkDeviceCaps()
{
	D3DCAPS9 caps;
	HR(md3dDev->GetDeviceCaps(&caps));

	// Check for vertex shader version 2.0 support.
	if( caps.VertexShaderVersion < D3DVS_VERSION(2, 0) )
		return false;

	// Check for pixel shader version 2.0 support.
	if( caps.PixelShaderVersion < D3DPS_VERSION(2, 0) )
		return false;

	return true;
}

void ShaderDemo::updateScene(float elapsed)
{
	
}

void ShaderDemo::drawScene()
{
	//=======================================
	// Camera Setup
	//=======================================
	myCamera->CreateCamera(0.1f, 50.0f);
	myCamera->moveCamera(D3DXVECTOR3(0.0f, 0.0f, -4.5f));
	myCamera->pointCamera(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	md3dDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//=======================================
	// Drawing Proper
	//=======================================
	md3dDev->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);
	md3dDev->BeginScene();

	md3dDev->SetVertexDeclaration(mVertexDecl);

	myCamera->DrawEffect(teapotMesh,
				   D3DXVECTOR3(1.0f, 1.0f, 1.0f), 
				   D3DXVECTOR3(0.0f, yRotation += 0.01f, 0.0f),
				   D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				   SH_WIREFRAME);


	md3dDev->EndScene();

	md3dDev->Present(NULL, NULL, NULL, NULL);
}