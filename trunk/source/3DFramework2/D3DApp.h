/////////////////////////////////////////////////////////////
/// D3DApp.h
///		This class is designed to be the "framework" for any
/// Direct3D Application. Any time a new D3D Application,
/// such as a game or otherwise, is created you can inherit
/// from this class and override the virtual functions for
/// updating and drawing.
///
/////////////////////////////////////////////////////////////

#include "d3dHelper.h"

class D3DApp
{
public:
	D3DApp(HINSTANCE hInstance, std::string title, D3DDEVTYPE devType,
		DWORD requestedVP);
	~D3DApp();

	HINSTANCE			GetAppInst();
	HWND				GetWindowHandle();
	LPDIRECT3D9			GetD3DObject();
	LPDIRECT3DDEVICE9	GetD3DDevice();
	
	//============================
	// Virtual Framework Methods
	//============================
	// Inherit and override these methods in order to extend the framework
	virtual void updateScene(float elapsed) {};
	virtual void drawScene()
	{ 
		md3dDev->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(100,139,247), 1.0f, 0);
		md3dDev->Present(0, 0, 0, 0);
	};
	
	//============================
	// Window & D3DDev Creation
	//============================
	virtual void initMainWindow();
	virtual void initDirect3D();
	virtual int run();

protected:
	std::string				mWindowTitle;
	D3DDEVTYPE				mDevType;
	DWORD					mRequestedVP;

	HINSTANCE				mAppInst;
	HWND					mhWnd;
	LPDIRECT3D9				md3d;
	LPDIRECT3DDEVICE9		md3dDev;
	D3DPRESENT_PARAMETERS	md3dPP;
};