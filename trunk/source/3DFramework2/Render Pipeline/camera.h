/////////////////////////////////////////////////////////////
/// camera.h
///		The camera class is designed to be used for the
/// rendering of 3-Dimensional Objects to screen space and
/// contains basic camera creation and manipulation methods.
///
/////////////////////////////////////////////////////////////

#ifndef CAMERA_H
#define CAMERA_H

#include ".\..\d3dHelper.h"

enum SHADER_TYPE
{
	SH_WIREFRAME
};

class camera
{
public:
	// Setup
	camera(LPDIRECT3DDEVICE9 d3dDev);
	void CreateCamera(float nearClip, float farClip);
	void initShader();

	// Camera Manipulation
	void moveCamera(D3DXVECTOR3 position);
	void pointCamera(D3DXVECTOR3 lookAtPos);

	// Rendering
	void Draw(LPD3DXMESH mesh, D3DXVECTOR3 scale, D3DXVECTOR3 objRotation, D3DXVECTOR3 objPosition);
	void DrawEffect(LPD3DXMESH mesh, D3DXVECTOR3 scale, D3DXVECTOR3 objRotation, D3DXVECTOR3 objPosition, SHADER_TYPE type);
private:
	LPDIRECT3DDEVICE9	md3dDev;				// D3D Device For Drawing

	D3DXMATRIX			mViewMatrix;			// The view matrix
	D3DXMATRIX			mProjectionMatrix;		// The projection matrix
	D3DXVECTOR3			mCameraPosition;		// The position of the camera
	D3DXVECTOR3			mCameraLook;			// Where the camera is pointing

	ID3DXEffect*		mEffect;
	D3DXHANDLE          mhTech;
	D3DXHANDLE          mhWVP;
};
#endif