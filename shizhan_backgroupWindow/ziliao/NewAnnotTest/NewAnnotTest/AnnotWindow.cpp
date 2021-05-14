#include "AnnotWindow.h"
#include <WindowsX.h>

#define BTN_HEIGHT	30
#define BTN_WIDTH	100
#define BTN_DRAG	30
#define TOOL_HEIGHT BTN_HEIGHT
#define TOOL_WIDTH (BTN_WIDTH * 3 + BTN_DRAG)

CSimpleTool::CSimpleTool(CAnnotWindow* pMain)
:m_pMain(pMain)
{

}

CSimpleTool::~CSimpleTool()
{

}

LRESULT CSimpleTool::OnEraseBkgnd(UINT, WPARAM, LPARAM, BOOL& bHandled)
{
	return TRUE;
}

LRESULT CSimpleTool::OnPaint(UINT, WPARAM, LPARAM, BOOL& bHandled)
{
	PAINTSTRUCT ps = {0};
	BeginPaint(m_hWnd, &ps);
	
	RECT rcClient = {0};
	GetClientRect(m_hWnd, &rcClient);
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
	FillRect(ps.hdc, &rcClient, hBrush);
	DeleteObject(hBrush);

	EndPaint(m_hWnd, &ps);

	return S_OK;
}


LRESULT CSimpleTool::OnCreate(UINT, WPARAM, LPARAM, BOOL& bHandled)
{
	INT arPos[] = { BTN_DRAG, BTN_DRAG + BTN_WIDTH, BTN_DRAG + BTN_WIDTH*2 };

	HINSTANCE hIns = _WinModule.GetModuleInstance();

	m_hDrawButton = CreateWindow(_T("BUTTON"), _T("Draw Mode"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
		arPos[0], 0, BTN_WIDTH, BTN_HEIGHT, m_hWnd, (HMENU)DRAW_MODE_ID, hIns, NULL);


	m_hDisplayButton = CreateWindow(_T("BUTTON"), _T("Display Mode"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
		arPos[1], 0, BTN_WIDTH, BTN_HEIGHT, m_hWnd, (HMENU)DISPLAY_MODE_ID, hIns, NULL);

	m_hExitButton = CreateWindow(_T("BUTTON"), _T("Exit"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
		arPos[2], 0, BTN_WIDTH, BTN_HEIGHT, m_hWnd, (HMENU)EXIT_BTN_ID, hIns, NULL);

	return S_OK;
}

LRESULT CSimpleTool::OnDestroy(UINT, WPARAM, LPARAM, BOOL& bHandled)
{
	return S_OK;
}

LRESULT CSimpleTool::OnLButtonDown(UINT, WPARAM wParam, LPARAM lParam, BOOL&)
{
	PostMessage(m_hWnd, WM_NCLBUTTONDOWN , HTCAPTION , lParam);	

	return S_OK;
}

LRESULT CSimpleTool::OnDrawMode(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pMain != NULL)
	{
		m_pMain->OnToolClick((DWORD)wID);
	}

	return S_OK;
}

LRESULT CSimpleTool::OnDisplayMode(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pMain != NULL)
	{
		m_pMain->OnToolClick((DWORD)wID);
	}

	return S_OK;
}

LRESULT CSimpleTool::OnExit(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_pMain != NULL)
	{
		m_pMain->OnToolClick((DWORD)wID);
	}

	return S_OK;
}

///////////////////  CAnnotWindow  /////////////////

CAnnotWindow::CAnnotWindow()
:m_tool(this)
{
	m_eAnnotMode = ANNOT_MODE_DRAW;
}

CAnnotWindow::~CAnnotWindow()
{

}

VOID CAnnotWindow::OnToolClick(DWORD dwBtnID)
{
	switch(dwBtnID)
	{
	case DRAW_MODE_ID:
		SetAnnotMode(ANNOT_MODE_DRAW);
		break;

	case DISPLAY_MODE_ID:
		SetAnnotMode(ANNOT_MODE_DISPLAY);
		break;

	case EXIT_BTN_ID:
		::DestroyWindow(m_hWnd);
		break;
	
	default:
		break;
	}
}

HWND CAnnotWindow::ShowWindow()
{
	if(m_hWnd != NULL && ::IsWindow(m_hWnd)) return m_hWnd;

	RECT rtScreen = {0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)};
	
	Create(NULL, rtScreen, NULL, WS_POPUP, WS_EX_TOPMOST | WS_EX_LAYERED, 0, NULL);
	if(::IsWindow(m_hWnd))
	{
		m_drawer.Initialize(m_hWnd, rtScreen.right - rtScreen.left, rtScreen.bottom - rtScreen.top);

		CheckAnnotMode();
		
		m_drawer.SetCanvas(m_hWnd);
		
		::ShowWindow(m_hWnd, SW_SHOW);
		UpdateWindow(m_hWnd);
	}

	return m_hWnd;
}

VOID CAnnotWindow::DestroyWindow()
{
	if(::IsWindow(m_hWnd))
	{
		::DestroyWindow(m_hWnd);
		m_hWnd = NULL;
	}

	m_drawer.Destroy();
}

VOID CAnnotWindow::SetAnnotMode(ANNOT_MODE eMode)
{
	m_eAnnotMode = eMode;

	CheckAnnotMode();
}

VOID CAnnotWindow::CheckAnnotMode()
{
	if(!::IsWindow(m_hWnd)) return;

	DWORD dwExStyle = GetWindowLong(m_hWnd, GWL_EXSTYLE);
	DWORD dwNewStyle = dwExStyle;
	if(m_eAnnotMode == ANNOT_MODE_DISPLAY)
	{
		dwNewStyle |= WS_EX_TRANSPARENT;
	}
	else //ANNOT_MODE_DRAW
	{
		dwNewStyle &= ~WS_EX_TRANSPARENT;
	}
		
	if(dwNewStyle != dwExStyle)
	{
		SetWindowLong(m_hWnd, GWL_EXSTYLE, dwNewStyle);
	}
}	

LRESULT CAnnotWindow::OnEraseBkgnd(UINT, WPARAM, LPARAM, BOOL& bHandled)
{
	return TRUE;
}

LRESULT CAnnotWindow::OnCreate(UINT, WPARAM, LPARAM, BOOL& bHandled)
{
	RECT rtWnd = {0};
	GetWindowRect(m_hWnd, &rtWnd);

	INT nPosX = rtWnd.right - 100;
	INT nPosY =  rtWnd.bottom - 150;
	RECT rcTool = { nPosX - TOOL_WIDTH, nPosY - TOOL_HEIGHT, nPosX, nPosY };

	m_tool.Create(m_hWnd, rcTool, NULL, WS_POPUP | WS_VISIBLE);

	return S_OK;
}


LRESULT CAnnotWindow::OnDestroy(UINT, WPARAM, LPARAM, BOOL& bHandled)
{
	PostQuitMessage(0);

	return S_OK;
}

LRESULT CAnnotWindow::OnLButtonDown(UINT, WPARAM, LPARAM lParam, BOOL&)
{
	SetCapture(m_hWnd);

	m_drawer.StartDraw(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

	return S_OK;
}

LRESULT CAnnotWindow::OnLButtonUp(UINT, WPARAM, LPARAM lParam, BOOL&)
{
	m_drawer.EndDraw(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

	ReleaseCapture();

	return S_OK;
}

LRESULT CAnnotWindow::OnMouseMove(UINT, WPARAM, LPARAM lParam, BOOL&)
{
	m_drawer.MoveDraw(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

	return S_OK;
}