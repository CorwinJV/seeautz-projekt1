#ifndef SHADERDEMO_H
#define SHADERDEMO_H

#include "D3DApp.h"
#include "Render Pipeline\\camera.h"


struct VertexPos
{
	VertexPos():pos(0.0f, 0.0f, 0.0f){}
	VertexPos(float x, float y, float z):pos(x,y,z){}
	VertexPos(const D3DXVECTOR3& v):pos(v){}

	D3DXVECTOR3 pos;
};

class ShaderDemo : public D3DApp
{
public:
	ShaderDemo(HINSTANCE hInstance, std::string title, D3DDEVTYPE devType, DWORD requestedVP);
	~ShaderDemo();
	bool checkDeviceCaps();

	void updateScene(float elapsed);
	void drawScene();
	void makeGridFloor();

private:
	camera* myCamera;
	LPD3DXMESH teapotMesh;
	LPDIRECT3DVERTEXDECLARATION9 mVertexDecl;

	DirectInput* di;


	float yRotation;

	float xCamPosition;
	float yCamPosition;
	float zCamPosition;
};

#endif