/////////////////////////////////////////////////////////////
/// D3DApp.cpp
///		Here's the definition for the D3D Framework.
/// Many of these functions can be overriden but should work
/// well with their default implementations.
///
/////////////////////////////////////////////////////////////

#include "D3DApp.h"

//===================================================
// WndProc
//	The windows callback function, not included in 
// the D3DApp class but required to handle messages. 
// 
//===================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}


//===================================================
// D3DApp
//	Class constructor. Sets certain local variables 
// required for the creation of a window and d3ddev
// 
//===================================================
D3DApp::D3DApp(HINSTANCE hInstance, std::string title, D3DDEVTYPE devType, DWORD requestedVP)
{
	mAppInst		= hInstance;
	mWindowTitle	= title;
	mDevType		= devType;
	mRequestedVP	= requestedVP;

	// private initialization
	mhWnd	= NULL;
	md3d	= NULL;
	md3dDev = NULL;
	ZeroMemory(&md3dPP, sizeof(md3dPP));

	initMainWindow();
	initDirect3D();
}
//===================================================
// ~D3DApp
//	Class destructor. Releases directX resources.
// 
//===================================================
D3DApp::~D3DApp()
{
	md3d->Release();
	md3dDev->Release();
}

//===================================================
// initMainWindow
//	Creates a window adhering to the Win32 paradims.
// 
//===================================================
void D3DApp::initMainWindow()
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style	= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = mAppInst;
	wcex.hIcon = 0; 
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "DirectXApplication";
	wcex.hIconSm = 0;
	RegisterClassEx(&wcex);

	mhWnd = CreateWindow("DirectXApplication",
						 mWindowTitle.c_str(),
						 WS_OVERLAPPEDWINDOW,
						 CW_USEDEFAULT,
						 CW_USEDEFAULT,
						 SCREEN_WIDTH,
						 SCREEN_HEIGHT,
						 NULL,
						 NULL,
						 mAppInst,
						 NULL);

	if(!mhWnd)
	{
		MessageBox(0, "Error initializing window", "Could not start app", MB_OK);
		PostQuitMessage(0);
	}

	ShowWindow(mhWnd, SW_SHOW);
	UpdateWindow(mhWnd);
}

//===================================================
// initDirect3D
//	Creates the Direct3D and Direct3DDevice objects,
// acquiring an interface to the video card and 
// allowing us to do cool stuff like draw to the
// screen!
// 
//===================================================
void D3DApp::initDirect3D()
{
	if(NULL == (md3d = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		MessageBox(0, "Error creating Direct3D Object", "Error", MB_OK);
		PostQuitMessage(0);
	}

	md3dPP.Windowed = true;
	md3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	md3dPP.BackBufferFormat = D3DFMT_UNKNOWN;
	md3dPP.BackBufferCount = 1;
	md3dPP.BackBufferWidth = SCREEN_WIDTH;
	md3dPP.BackBufferHeight = SCREEN_HEIGHT;
	md3dPP.hDeviceWindow = mhWnd;
	md3dPP.EnableAutoDepthStencil = TRUE;
	md3dPP.AutoDepthStencilFormat = D3DFMT_D16;

	if(FAILED(md3d->CreateDevice(D3DADAPTER_DEFAULT, mDevType, mhWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&md3dPP, &md3dDev)))
	{
		MessageBox(0, "Error creating Direct3D Device", "Error", MB_OK);
		PostQuitMessage(0);
	}

	// Set the default render state
	md3dDev->SetRenderState(D3DRS_ZENABLE, TRUE);
	md3dDev->SetRenderState(D3DRS_LIGHTING, FALSE);
}

//===================================================
// run
//	Creates a 'real-time game loop' which provides us
// with a means to update game objects and render them
// in real time
// 
//===================================================
int D3DApp::run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while(msg.message != WM_QUIT)
	{
		// Check for messages
		if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{ // This is called when there are no messages pending
			updateScene(0.0f);
			drawScene();
		}
	}
	return (int)msg.wParam;
}

//==============================
// Get Accessors
//==============================
HINSTANCE D3DApp::GetAppInst()
{
	return mAppInst;
}

LPDIRECT3DDEVICE9 D3DApp::GetD3DDevice()
{
	return md3dDev;
}

LPDIRECT3D9 D3DApp::GetD3DObject()
{
	return md3d;
}

HWND D3DApp::GetWindowHandle()
{
	return mhWnd;
}