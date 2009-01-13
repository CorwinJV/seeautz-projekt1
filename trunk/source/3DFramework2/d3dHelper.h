#ifndef D3DHELPER_H
#define D3DHELPER_H

#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr9.h>
#include <string>
#include <sstream>
#include "DirectInput.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Extra d3d debugging info if in debug mode.
#if defined(DEBUG) | defined(_DEBUG)
#ifndef D3D_DEBUG_INFO
#define D3D_DEBUG_INFO
#endif
#endif


#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
	#define HR(x)                                      \
	{                                                  \
		HRESULT hr = x;                                \
		if(FAILED(hr))                                 \
		{                                              \
			DXTrace(__FILE__, __LINE__, hr, #x, TRUE); \
		}                                              \
	}
	#endif

#else
	#ifndef HR
	#define HR(x) x;
	#endif
#endif 


#endif