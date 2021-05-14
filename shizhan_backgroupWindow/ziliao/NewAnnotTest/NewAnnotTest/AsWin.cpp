#include "AsWin.h"

/////////////////////////////  CWindowImplBase ////////////////////////////
LRESULT CALLBACK CWindowImplBase::StartWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CWindowImplBase* pThis = (CWindowImplBase*)_WinModule.ExtractCreateWndData();
	assert(pThis != NULL);
	if(!pThis)
	{
		return 0;
	}
	pThis->m_hWnd = hWnd;

	// Initialize the thunk.  This is allocated in CWindowImplBase::Create,
	// so failure is unexpected here.

	pThis->m_thunk.Init(pThis->GetWindowProc(), pThis);
	WNDPROC pProc = pThis->m_thunk.GetWNDPROC();
	WNDPROC pOldProc = (WNDPROC)::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)pProc);
#ifdef _DEBUG
	// check if somebody has subclassed us already since we discard it
	if(pOldProc != StartWindowProc)
		assert(false);
#else
	(pOldProc);	// avoid unused warning
#endif
	return pProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK CWindowImplBase::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CWindowImplBase* pThis = (CWindowImplBase*)hWnd;
	// set a ptr to this message and save the old value
	WIN_MSG msg(pThis->m_hWnd, uMsg, wParam, lParam);
	const WIN_MSG* pOldMsg = pThis->m_pCurrentMsg;
	pThis->m_pCurrentMsg = &msg;
	// pass to the message map to process
	LRESULT lRes;
	BOOL bRet = pThis->ProcessWindowMessage(pThis->m_hWnd, uMsg, wParam, lParam, lRes, 0);
	// restore saved value for the current message
	assert(pThis->m_pCurrentMsg == &msg);

	// do the default processing if message was not handled
	if(!bRet)
	{
		if(uMsg != WM_NCDESTROY)
			lRes = pThis->DefWindowProc(uMsg, wParam, lParam);
		else
		{
			// unsubclass, if needed
			LONG_PTR pfnWndProc = ::GetWindowLongPtr(pThis->m_hWnd, GWLP_WNDPROC);
			lRes = pThis->DefWindowProc(uMsg, wParam, lParam);
			if(pThis->m_pfnSuperWindowProc != ::DefWindowProc && ::GetWindowLongPtr(pThis->m_hWnd, GWLP_WNDPROC) == pfnWndProc)
				::SetWindowLongPtr(pThis->m_hWnd, GWLP_WNDPROC, (LONG_PTR)pThis->m_pfnSuperWindowProc);
			// mark window as destryed
			pThis->m_dwState |= WINSTATE_DESTROYED;
		}
	}
	if((pThis->m_dwState & WINSTATE_DESTROYED) && pOldMsg== NULL)
	{
		// clear out window handle
		HWND hWndThis = pThis->m_hWnd;
		pThis->m_hWnd = NULL;
		pThis->m_dwState &= ~WINSTATE_DESTROYED;
		// clean up after window is destroyed
		pThis->m_pCurrentMsg = pOldMsg;
		pThis->OnFinalMessage(hWndThis);
	}else {
		pThis->m_pCurrentMsg = pOldMsg;
	}
	return lRes;
}

HWND CWindowImplBase::Create(HWND hWndParent, RECT rect, LPCTSTR szWindowName,
							 DWORD dwStyle, DWORD dwExStyle, UINT MenuOrID, ATOM atom, LPVOID lpCreateParam)
{
	BOOL result;
	assert(m_hWnd == NULL);

	if(m_hWnd != NULL) return m_hWnd;

	// Allocate the thunk structure here, where we can fail gracefully.
	result = m_thunk.Init(NULL,NULL);
	if (result == FALSE) {
		SetLastError(ERROR_OUTOFMEMORY);
		return NULL;
	}

	if(atom == 0)
	{
		assert(FALSE);
		return NULL;
	}

	_WinModule.AddCreateWndData(&m_thunk.cd, this);

	HWND hWnd = ::CreateWindowEx(dwExStyle, MAKEINTATOM(atom), szWindowName,
		dwStyle, rect.left, rect.top, rect.right - rect.left,
		rect.bottom - rect.top, hWndParent, (HMENU)MenuOrID,
		_WinModule.GetModuleInstance(), lpCreateParam);

	assert(m_hWnd == hWnd);

	return hWnd;
}
/////////////////////////////  CWindowImplBase ////////////////////////////


/////////////////////////////  CCSLockGuard ////////////////////////////
class CCSLockGuard
{
public:
	static void InitCS(CRITICAL_SECTION& cs)
	{
		::InitializeCriticalSection(&cs);
	}

	static void DeleteCS(CRITICAL_SECTION& cs)
	{
		::DeleteCriticalSection(&cs);
	}

	CCSLockGuard(CRITICAL_SECTION& cs)
		:m_cs(cs)
	{
		EnterCriticalSection(&m_cs);
	}

	~CCSLockGuard()
	{
		LeaveCriticalSection(&m_cs);
	}

private:
	CRITICAL_SECTION& m_cs;
};
/////////////////////////////  CCSLockGuard ////////////////////////////


/////////////////////////////  CWinModule ////////////////////////////
CWinModule::CWinModule()
: m_hModuleInstance(NULL), m_pCreateWndList(NULL), m_bInited(FALSE)
{

}

CWinModule::~CWinModule()
{
	Term();
}

BOOL CWinModule::Initialize(HINSTANCE hInstance)
{
	m_hModuleInstance = hInstance;

	if(m_hModuleInstance == NULL)
	{
		m_hModuleInstance = GetModuleHandle(NULL);
	}

	if(!m_bInited)
	{
		CCSLockGuard::InitCS(m_csWinCreate);
		m_bInited = TRUE;
	}

	return TRUE;
}

void CWinModule::Term()
{
	if(!m_bInited) return;

	UnregisterAllClass();

	CCSLockGuard::DeleteCS(m_csWinCreate);

	m_bInited = FALSE;
}

HINSTANCE CWinModule::GetModuleInstance() const
{
	return m_hModuleInstance;
}

void CWinModule::AddCreateWndData(CCreateWndData* pData, void* pObject)
{
	assert(m_bInited);
	if(!m_bInited) return;

	assert(pData != NULL && pObject != NULL);

	pData->m_pThis = pObject;
	pData->m_dwThreadID = ::GetCurrentThreadId();

	CCSLockGuard lock(m_csWinCreate);
	{
		pData->m_pNext = m_pCreateWndList;
		m_pCreateWndList = pData;
	}
}

void* CWinModule::ExtractCreateWndData()
{
	assert(m_bInited);
	if(!m_bInited) return NULL;

	void* pv = NULL;

	CCSLockGuard lock(m_csWinCreate);
	{
		CCreateWndData* pEntry = m_pCreateWndList;
		if(pEntry != NULL)
		{
			DWORD dwThreadID = ::GetCurrentThreadId();
			CCreateWndData* pPrev = NULL;
			while(pEntry != NULL)
			{
				if(pEntry->m_dwThreadID == dwThreadID)
				{
					if(pPrev == NULL)
						m_pCreateWndList = pEntry->m_pNext;
					else
						pPrev->m_pNext = pEntry->m_pNext;
					pv = pEntry->m_pThis;
					break;
				}
				pPrev = pEntry;
				pEntry = pEntry->m_pNext;
			}
		}
	}

	return pv;
}

ATOM CWinModule::RegisterWndClass(CWndClassInfo& classInfo)
{
	assert(m_bInited);
	if(!m_bInited) return NULL;

	do
	{
		if(classInfo.m_atom != 0) break;

		CCSLockGuard lock(m_csWinCreate);
		{
			if(classInfo.m_atom != 0) break;

			if(classInfo.m_wc.hCursor == NULL)
			{
				classInfo.m_wc.hCursor = LoadCursor(NULL, IDC_ARROW);
			}

			classInfo.m_wc.hInstance = _WinModule.GetModuleInstance();
			classInfo.m_wc.style &= ~CS_GLOBALCLASS;	// we don't register global classes

			if (classInfo.m_wc.lpszClassName == NULL)
			{
#if defined(_WIN64) // || or Windows 2000
				::wsprintfW(classInfo.m_szAutoName, L"AS:%p", &classInfo.m_wc);
#else
				::wsprintfW(classInfo.m_szAutoName, L"AS:%8.8X", reinterpret_cast<DWORD_PTR>(&classInfo.m_wc));
#endif
				classInfo.m_wc.lpszClassName = classInfo.m_szAutoName;
			}

			WNDCLASSEX wcTemp;
			wcTemp = classInfo.m_wc;
			classInfo.m_atom = static_cast<ATOM>(GetClassInfoEx(classInfo.m_wc.hInstance, classInfo.m_wc.lpszClassName, &wcTemp));
			if (classInfo.m_atom == 0)
			{
				classInfo.m_atom = RegisterClassEx( &classInfo.m_wc);

				if(classInfo.m_atom != 0)
				{
					m_arRegisterClass.push_back(classInfo.m_atom);
				}
				else
				{
					assert(false);
				}
			}
		}
	}
	while(false);

	assert(classInfo.m_atom != 0);

	return classInfo.m_atom;
}

void CWinModule::UnregisterAllClass()
{
	if(!m_bInited) return;

	CCSLockGuard lock(m_csWinCreate);
	{
		if(!m_arRegisterClass.empty())
		{
			size_t nCount = m_arRegisterClass.size();
			for(size_t i=0; i<nCount; ++i)
			{
				UnregisterClass((LPCTSTR)m_arRegisterClass[i], m_hModuleInstance);
			}

			m_arRegisterClass.clear();
		}
	}
}
/////////////////////////////  CWinModule ////////////////////////////