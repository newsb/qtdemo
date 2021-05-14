#ifndef __ANNOT_WINDOW_H__
#define __ANNOT_WINDOW_H__

#include "AsWin.h"
#include <tchar.h>
#include "AnnotImage.h"

#define DRAW_MODE_ID		100
#define DISPLAY_MODE_ID		101
#define EXIT_BTN_ID			120

enum ANNOT_MODE
{
	ANNOT_MODE_DRAW,	//do annotation
	ANNOT_MODE_DISPLAY  //display only
};

class CAnnotWindow;

class CSimpleTool: public CWindowImpl<CSimpleTool>
{
public:
	DECLARE_WND_CLASS(_T("CSimpleTool"))
	
	CSimpleTool(CAnnotWindow* pMain);
	~CSimpleTool();

	BEGIN_MSG_MAP(CSimpleTool)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)

		COMMAND_ID_HANDLER(DRAW_MODE_ID, OnDrawMode)
		COMMAND_ID_HANDLER(DISPLAY_MODE_ID, OnDisplayMode)
		COMMAND_ID_HANDLER(EXIT_BTN_ID, OnExit)
	END_MSG_MAP()
	
private:
	LRESULT OnEraseBkgnd(UINT, WPARAM, LPARAM, BOOL& bHandled);
	LRESULT OnPaint(UINT, WPARAM, LPARAM, BOOL& bHandled);

	LRESULT OnCreate(UINT, WPARAM, LPARAM, BOOL& bHandled);
	LRESULT OnDestroy(UINT, WPARAM, LPARAM, BOOL& bHandled);

	LRESULT OnLButtonDown(UINT, WPARAM wParam, LPARAM lParam, BOOL&);

	LRESULT OnDrawMode(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnDisplayMode(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

private:
	HWND m_hDrawButton;
	HWND m_hDisplayButton;
	HWND m_hExitButton;

	CAnnotWindow* m_pMain;
};

class CAnnotWindow: CWindowImpl<CAnnotWindow>
{
public:
	DECLARE_WND_CLASS(_T("CAnnotWindow"))

	BEGIN_MSG_MAP(CAnnotWindow)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)

		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	END_MSG_MAP()

	CAnnotWindow();
	~CAnnotWindow();

	HWND ShowWindow();
	VOID DestroyWindow();
		
	VOID SetAnnotMode(ANNOT_MODE eMode);

	VOID OnToolClick(DWORD dwBtnID);

private:
	LRESULT OnEraseBkgnd(UINT, WPARAM, LPARAM, BOOL& bHandled);

	LRESULT OnCreate(UINT, WPARAM, LPARAM, BOOL& bHandled);
	LRESULT OnDestroy(UINT, WPARAM, LPARAM, BOOL& bHandled);

	LRESULT OnLButtonDown(UINT, WPARAM, LPARAM lParam, BOOL&);
	LRESULT OnLButtonUp(UINT, WPARAM, LPARAM lParam, BOOL&);
	LRESULT OnMouseMove(UINT, WPARAM, LPARAM lParam, BOOL&);

private:
	VOID CheckAnnotMode();

private:
	ANNOT_MODE m_eAnnotMode;
	CAnnotDrawer m_drawer;
	CSimpleTool m_tool;
};

#endif //__ANNOT_WINDOW_H__