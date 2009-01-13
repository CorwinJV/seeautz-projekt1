//#define spinning_demo

#ifdef spinning_demo
#include "SpinningBoxDemo.h"
#else
#include "ShaderDemo.h"
#endif

///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// WinMain()
/// This function is the entry point for any Win32 app
/// and as such is not apart of the D3DApp or HelloD3DApp 
/// implementation.
///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{
#ifdef spinning_demo
	SpinningBoxDemo* game = new SpinningBoxDemo(hInstance, "Awesome wee", D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING);
#else
	ShaderDemo* game = new ShaderDemo(hInstance, "Awesome wee", D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING);
#endif


	game->run();
}
///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
