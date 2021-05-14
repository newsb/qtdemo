#include "AnnotWindow.h"

#include "./gdiplus/GdiPlus.h"
using namespace  Gdiplus;

#pragma comment(lib, "gdiplus/gdiplus.lib")

CWinModule _WinModule;

int WINAPI WinMain( HINSTANCE hInstance,
				    HINSTANCE hPrevInstance,
				    LPSTR lpCmdLine,
				    int nShowCmd)
{
	GdiplusStartupInput gs;
	ULONG_PTR token;
	GdiplusStartup(&token, &gs, NULL);

	_WinModule.Initialize(hInstance);

	CAnnotWindow annotWin;
	annotWin.ShowWindow();

	MSG msg = {0};
	while(GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	_WinModule.Term();

	GdiplusShutdown(token);

	return 0;
}