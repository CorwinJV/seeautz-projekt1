/////////////////////////////////////////////////////////////
/// camera.cpp
///		Here's the definition for the camera class. 
/// These functions deal with the creation and manipulation
/// of a camera in 3-Dimensional space as well as the rendering
/// of objects seen via that camera. 
///
/////////////////////////////////////////////////////////////

#include "camera.h"


camera::camera(LPDIRECT3DDEVICE9 d3dDev)
{
	md3dDev = d3dDev;

	initShader();
}

void camera::initShader()
{
	// Create the FX from a .fx file.
	ID3DXBuffer* errors = 0;
	HR(D3DXCreateEffectFromFile(md3dDev, "transform.fx", 
		0, 0, D3DXSHADER_DEBUG, 0, &mEffect, &errors));
	if( errors )
		MessageBox(0, (char*)errors->GetBufferPointer(), 0, 0);

	// Obtain handles.
	mhTech = mEffect->GetTechniqueByName("TransformTech");
	mhWVP  = mEffect->GetParameterByName(0, "gWVP");
}



void camera::CreateCamera(float nearClip, float farClip)
{
	// Here we specify the field of view, 
	// aspect ratio and near / far clipping planes
	D3DXMatrixPerspectiveFovLH(&mProjectionMatrix, D3DX_PI * 0.25f, SCREEN_WIDTH/SCREEN_HEIGHT, nearClip, farClip);
	md3dDev->SetTransform(D3DTS_PROJECTION, &mProjectionMatrix);
}

void camera::moveCamera(D3DXVECTOR3 position)
{
	mCameraPosition = position;
}

void camera::pointCamera(D3DXVECTOR3 lookAtPos)
{
	mCameraLook = lookAtPos;
	D3DXMatrixLookAtLH(&mViewMatrix,					
					   &mCameraPosition,				// Camera's position
					   &mCameraLook,					// Where the camera's looking
					   &D3DXVECTOR3(0.0f, 1.0f, 0.0f));	// UP Vector

	md3dDev->SetTransform(D3DTS_VIEW, &mViewMatrix);
}

// This function performs all of the necessary transformations on a mesh
// to properly render it to the screen. 
void camera::Draw(LPD3DXMESH mesh, D3DXVECTOR3 scale, D3DXVECTOR3 objRotation, D3DXVECTOR3 objPosition)
{
	D3DXMATRIX matScale;
	D3DXMATRIX matRot;
	D3DXMATRIX matRotX;
	D3DXMATRIX matRotY;
	D3DXMATRIX matRotZ;
	D3DXMATRIX matTrans;
	D3DXMATRIX matFinal;
	D3DXMATRIX matWorld;

	// Calculate Scaling
	D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);

	// Calculate Rotation
	D3DXMatrixRotationX(&matRotX, objRotation.x);
	D3DXMatrixRotationY(&matRotY, objRotation.y);
	D3DXMatrixRotationZ(&matRotZ, objRotation.z);
	D3DXMatrixMultiply(&matRot, &matRotX, &matRotY);
	D3DXMatrixMultiply(&matRot, &matRot, &matRotZ);

	// Add Translation (position)
	D3DXMatrixTranslation(&matTrans, objPosition.x, objPosition.y, objPosition.z);

	// Multiply all of the matrices together
	D3DXMatrixMultiply(&matFinal, &matScale, &matRot);
	D3DXMatrixMultiply(&matFinal, &matFinal, &matTrans);

	// Create & set world matrix from scale/rot/trans and view
	D3DXMatrixMultiply(&matWorld, &matFinal, &mViewMatrix);
	md3dDev->SetTransform(D3DTS_WORLD, &matWorld);
	
	// And finally... Draw To The Screen
	mesh->DrawSubset(0);
}

void camera::DrawEffect(LPD3DXMESH mesh, D3DXVECTOR3 scale, D3DXVECTOR3 objRotation, D3DXVECTOR3 objPosition, SHADER_TYPE type)
{
	D3DXMATRIX matScale;
	D3DXMATRIX matRot;
	D3DXMATRIX matRotX;
	D3DXMATRIX matRotY;
	D3DXMATRIX matRotZ;
	D3DXMATRIX matTrans;
	D3DXMATRIX matFinal;
	D3DXMATRIX matWorld;

	// Calculate Scaling
	D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);

	// Calculate Rotation
	D3DXMatrixRotationX(&matRotX, objRotation.x);
	D3DXMatrixRotationY(&matRotY, objRotation.y);
	D3DXMatrixRotationZ(&matRotZ, objRotation.z);
	D3DXMatrixMultiply(&matRot, &matRotX, &matRotY);
	D3DXMatrixMultiply(&matRot, &matRot, &matRotZ);

	// Add Translation (position)
	D3DXMatrixTranslation(&matTrans, objPosition.x, objPosition.y, objPosition.z);

	// Multiply all of the matrices together
	D3DXMatrixMultiply(&matFinal, &matScale, &matRot);
	D3DXMatrixMultiply(&matFinal, &matFinal, &matTrans);

	// Create & set world matrix from scale/rot/trans and view
	D3DXMatrixMultiply(&matWorld, &matFinal, &mViewMatrix);
	md3dDev->SetTransform(D3DTS_WORLD, &matWorld);

	//=================
	// Shader Stuff!
	mEffect->SetTechnique(mhTech);
	mEffect->SetMatrix(mhWVP, &((matWorld * mProjectionMatrix)));

	// Begin Passes
	UINT numPasses = 0;
	mEffect->Begin(&numPasses, NULL);
	for(UINT i = 0; i < numPasses; i++)
	{
		mEffect->BeginPass(i);
			mesh->DrawSubset(0);
		mEffect->EndPass();
	}
	mEffect->End();
	
}