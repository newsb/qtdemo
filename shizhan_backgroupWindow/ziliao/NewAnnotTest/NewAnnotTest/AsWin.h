#ifndef __AS_WIN_H__
#define __AS_WIN_H__

#include "StdThunk.h"

#include <assert.h>
#include <vector>

#define BEGIN_MSG_MAP(theClass) \
public: \
	BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID = 0) \
	{ \
	BOOL bHandled = TRUE; \
	(hWnd); \
	(uMsg); \
	(wParam); \
	(lParam); \
	(lResult); \
	(bHandled); \
	switch(dwMsgMapID) \
		{ \
	case 0:

#define MESSAGE_HANDLER(msg, func) \
	if(uMsg == msg) \
	{ \
	bHandled = TRUE; \
	lResult = func(uMsg, wParam, lParam, bHandled); \
	if(bHandled) \
	return TRUE; \
	}

#define COMMAND_ID_HANDLER(id, func) \
	if(uMsg == WM_COMMAND && id == LOWORD(wParam)) \
	{ \
	bHandled = TRUE; \
	lResult = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
	if(bHandled) \
	return TRUE; \
	}

#define END_MSG_MAP() \
	break; \
		default: \
		assert(FALSE); \
		break; \
		} \
		return FALSE; \
	}

struct WIN_MSG : public MSG
{
public:
	int cbSize;
	BOOL bHandled;

	WIN_MSG() : cbSize(sizeof(WIN_MSG)), bHandled(TRUE)
	{
		hwnd = NULL;
		message = 0;
		wParam = 0;
		lParam = 0;
		time = 0;
		pt.x = pt.y = 0;
	}

	WIN_MSG(HWND hWnd, UINT uMsg, WPARAM wParamIn, LPARAM lParamIn, DWORD dwTime, POINT ptIn, BOOL bHandledIn)
		: cbSize(sizeof(WIN_MSG)), bHandled(bHandledIn)
	{
		hwnd = hWnd;
		message = uMsg;
		wParam = wParamIn;
		lParam = lParamIn;
		time = dwTime;
		pt = ptIn;
	}

	WIN_MSG(HWND hWnd, UINT uMsg, WPARAM wParamIn, LPARAM lParamIn, BOOL bHandledIn = TRUE)
		: cbSize(sizeof(WIN_MSG)), bHandled(bHandledIn)
	{
		hwnd = hWnd;
		message = uMsg;
		wParam = wParamIn;
		lParam = lParamIn;
		time = 0;
		pt.x = pt.y = 0;
	}

	WIN_MSG(MSG& msg, BOOL bHandledIn = TRUE) 
		: cbSize(sizeof(WIN_MSG)), bHandled(bHandledIn)
	{
		hwnd = msg.hwnd;
		message = msg.message;
		wParam = msg.wParam;
		lParam = msg.lParam;
		time = msg.time;
		pt = msg.pt;
	}
};

class CWndClassInfo
{
public:
	WNDCLASSEX m_wc;
	ATOM m_atom;
	WCHAR m_szAutoName[5+sizeof(void*)*CHAR_BIT];
};

#define DECLARE_WND_CLASS(WndClassName) \
	static CWndClassInfo& GetWndClassInfo() \
{ \
	static CWndClassInfo wc = \
{ \
{ sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, StartWindowProc, \
	0, 0, NULL, NULL, NULL, (HBRUSH)(COLOR_WINDOW + 1), NULL, WndClassName, NULL }, \
	0, _T("") \
}; \
	return wc; \
}


struct CCreateWndData
{
	void* m_pThis;
	DWORD m_dwThreadID;
	CCreateWndData* m_pNext;
};

class CWndProcThunk
{
public:
	CCreateWndData cd;
	CStdCallThunk thunk;

	BOOL Init(WNDPROC proc, void* pThis)
	{
		return thunk.Init((DWORD_PTR)proc, pThis);
	}

	WNDPROC GetWNDPROC()
	{
		return (WNDPROC)thunk.GetCodeAddress();
	}
};

class  CMessageMap
{ 
public:
	virtual BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
		LRESULT& lResult, DWORD dwMsgMapID) = 0;
};


class  CWindowImplRoot:  public CMessageMap
{
public:
	CWndProcThunk m_thunk;
	const WIN_MSG* m_pCurrentMsg;
	DWORD m_dwState;
	HWND m_hWnd;

	enum { WINSTATE_DESTROYED = 0x00000001 };

	CWindowImplRoot():m_hWnd(NULL),m_pCurrentMsg(NULL), m_dwState(0)
	{ }

	virtual ~CWindowImplRoot()
	{
		// should be cleared in WindowProc
		if(m_hWnd != NULL)	
		{
			assert(false);
		}
	}

	const WIN_MSG* GetCurrentMessage() const
	{
		return m_pCurrentMsg;
	}

	BOOL IsMsgHandled() const
	{
		const WIN_MSG* pMsg = GetCurrentMessage();
		assert(pMsg != NULL);
		assert(pMsg->cbSize >= sizeof(WIN_MSG));
		return pMsg->bHandled;
	}
	void SetMsgHandled(BOOL bHandled)
	{
		WIN_MSG* pMsg = (WIN_MSG*)GetCurrentMessage();
		assert(pMsg != NULL);
		assert(pMsg->cbSize >= sizeof(WIN_MSG));
		pMsg->bHandled = bHandled;
	}
};

class  CWindowImplBase: public CWindowImplRoot
{
public:
	WNDPROC m_pfnSuperWindowProc;

	CWindowImplBase():m_pfnSuperWindowProc(::DefWindowProc)
	{}

	virtual WNDPROC GetWindowProc()
	{
		return WindowProc;
	}

	static LRESULT CALLBACK StartWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND Create(HWND hWndParent, RECT rect, LPCTSTR szWindowName,
		DWORD dwStyle, DWORD dwExStyle, UINT MenuOrID, ATOM atom, LPVOID lpCreateParam = NULL);

	BOOL DestroyWindow()
	{
		assert(::IsWindow(m_hWnd));
		return ::DestroyWindow(m_hWnd);
	}

	LRESULT DefWindowProc()
	{
		const WIN_MSG* pMsg = m_pCurrentMsg;
		LRESULT lRes = 0;
		if (pMsg != NULL)
			lRes = DefWindowProc(pMsg->message, pMsg->wParam, pMsg->lParam);
		return lRes;
	}

	LRESULT DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		return ::CallWindowProc(m_pfnSuperWindowProc, m_hWnd, uMsg, wParam, lParam);
	}

	virtual void OnFinalMessage(HWND /*hWnd*/)
	{
		// override to do something, if needed
	}
};

template <typename T>
class  CWindowImpl : public CWindowImplBase
{
public:
	DECLARE_WND_CLASS(NULL)

	HWND Create(HWND hWndParent, RECT rect, LPCTSTR szWindowName = NULL,
		DWORD dwStyle = 0, DWORD dwExStyle = 0,
		UINT MenuOrID = 0U, LPVOID lpCreateParam = NULL)
	{
		ATOM atom = _WinModule.RegisterWndClass(T::GetWndClassInfo());

		return CWindowImplBase::Create(hWndParent, rect, szWindowName,
			dwStyle, dwExStyle, MenuOrID, atom, lpCreateParam);
	}
};

class CWinModule
{
public:
	CWinModule();
	~CWinModule();

	BOOL Initialize(HINSTANCE hInstance);
	void Term();

	HINSTANCE GetModuleInstance() const;

	void AddCreateWndData(CCreateWndData* pData, void* pObject);
	void* ExtractCreateWndData();

	ATOM RegisterWndClass(CWndClassInfo& classInfo);

protected:
	void UnregisterAllClass();

private:
	HINSTANCE m_hModuleInstance;
	CCreateWndData* m_pCreateWndList;	//save the [this] pointer
	BOOL m_bInited;
	CRITICAL_SECTION m_csWinCreate;		//multi-thread support for window register/create
	std::vector<ATOM> m_arRegisterClass;//registered window classes, need unregister when unload module
};

extern CWinModule _WinModule;

#endif //__AS_WIN_H__