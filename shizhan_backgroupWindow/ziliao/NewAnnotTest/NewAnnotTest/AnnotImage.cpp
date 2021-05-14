#include "AnnotImage.h"

using namespace  Gdiplus;


/////////////  CAnnotImage  ////////////

CAnnotImage::CAnnotImage()
:m_nWidth(0), m_nHeight(0), m_pGraphic(NULL), m_hDC(NULL), m_hBmpOld(NULL)
{

}

CAnnotImage::~CAnnotImage()
{

}

BOOL CAnnotImage::Initialize(HWND hWnd, INT nWidth, INT nHeight)
{
	Destroy();

	m_nWidth = nWidth;
	m_nHeight = nHeight;

	HDC dcWnd = GetDC(hWnd);
	m_hDC = CreateCompatibleDC(dcWnd);
	ReleaseDC(hWnd, dcWnd);

	m_dib.Create(m_hDC, m_nWidth, m_nHeight, 32);
	m_hBmpOld = (HBITMAP)SelectObject(m_hDC, m_dib.GetBitmap());

	m_pGraphic = Graphics::FromHDC(m_hDC);

//	InitImage();
	
// 	CAnnotItem* p = new CAnnotItem;
// 	p->m_clr = Color(100, 0, 0, 255);
// 	p->nPenWidth = 10;
// 	POINT p1 = {0, 0};
// 	POINT p2 = {100, 100};
// 	POINT p3 = {400, 200};
// 	p->m_arPoint.push_back(p1);
// 	p->m_arPoint.push_back(p2);
// 	p->m_arPoint.push_back(p3);
// 	m_arData.push_back(p);

	return TRUE;
}

VOID CAnnotImage::Destroy()
{
	if(m_pGraphic != NULL)
	{
		delete m_pGraphic;
		m_pGraphic = NULL;
	}

	if(m_hBmpOld != NULL)
	{
		SelectObject(m_hDC, m_hBmpOld);
		m_hBmpOld = NULL;
	}

	if(m_hDC != NULL)
	{
		DeleteDC(m_hDC);
		m_hDC = NULL;
	}

	if(!m_dib.IsNull())
	{
		m_dib.Destroy();
	}

	ClearData();

	m_nWidth = 0;
	m_nHeight = 0;
}

VOID CAnnotImage::UpdateLayeredContent(HWND hWnd)
{
	DrawContent();

	HDC dcWnd = GetDC(hWnd);
	
	BLENDFUNCTION blf;
	blf.BlendOp = AC_SRC_OVER;
	blf.BlendFlags = 0;
	blf.SourceConstantAlpha = 255;
	blf.AlphaFormat = AC_SRC_ALPHA;

	RECT rcWnd = {0};
	GetWindowRect(hWnd, &rcWnd);
	SIZE sizeWnd = {rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top};
	POINT ptWnd = {rcWnd.left, rcWnd.top};
	POINT ptSrc = {0};
	UpdateLayeredWindow(hWnd, dcWnd, &ptWnd, &sizeWnd, m_hDC, &ptSrc, 0, &blf, ULW_ALPHA);

	ReleaseDC(hWnd, dcWnd);
}

VOID CAnnotImage::AddStroke(CAnnotItem* pItem)
{
	m_arData.push_back(pItem);
}

VOID CAnnotImage::InitImage()
{
// 	if(m_dib.IsNull()) return;
// 
// 	DWORD dwTransparent(0x05000000);
// 	DWORD* pData = (DWORD*)m_dib.GetRawData();
// 	for(INT i=0;i <m_nHeight; ++i)
// 	{
// 		for(INT k=0; k<m_nWidth; ++k)
// 		{
// 			pData[k + i * m_nWidth] = dwTransparent;
// 		}
// 	}

	if(m_pGraphic == NULL) return;
	Color clr(5, 0, 0, 0); //alpha = 1
	m_pGraphic->Clear(clr);
}

VOID CAnnotImage::ClearData()
{
	INT nCount = m_arData.size();
	for(INT i=0; i<nCount; ++i)
	{
		delete m_arData[i];
	}

	m_arData.clear();
}

VOID CAnnotImage::DrawItem(CAnnotItem* pItem)
{
	if(pItem->m_arPoint.size() == 0) return;

	Pen pen(pItem->m_clr, pItem->nPenWidth);
	m_pGraphic->DrawLines(&pen, (Point*)&(pItem->m_arPoint[0]), pItem->m_arPoint.size());
}

VOID CAnnotImage::DrawContent()
{
	InitImage();

	INT nCount = m_arData.size();
	for(INT i=0; i<nCount; ++i)
	{
		DrawItem(m_arData[i]);
	}
}


/////////////  CAnnotImage  ////////////

CAnnotDrawer::CAnnotDrawer()
:m_pCurrentItem(NULL)
{

}

CAnnotDrawer::~CAnnotDrawer()
{

}

BOOL CAnnotDrawer::Initialize(HWND hWnd, INT nWidth, INT nHeight)
{
	BOOL bRet = m_image.Initialize(hWnd, nWidth, nHeight);

	return bRet;
}

VOID CAnnotDrawer::Destroy()
{
	m_image.Destroy();
}

VOID CAnnotDrawer::SetCanvas(HWND hWnd)
{
	m_hWndCanvas = hWnd;

	m_image.UpdateLayeredContent(hWnd);
}

VOID CAnnotDrawer::InitItem(CAnnotItem* pItem)
{
	INT MIN_TRANSPARENT = 50;
	INT MAX_PEN_WIDTH = 40;
	INT MIN_PEN_WIDTH = 5;

	BYTE a = (double)rand() / RAND_MAX * 255;
	BYTE r = (double)rand() / RAND_MAX * 255;
	BYTE g = (double)rand() / RAND_MAX * 255;
	BYTE b = (double)rand() / RAND_MAX * 255;

	INT nPenWidth = (double)rand() / RAND_MAX * MAX_PEN_WIDTH;

	if(nPenWidth <= MIN_PEN_WIDTH) nPenWidth = MIN_PEN_WIDTH;
	if(a < MIN_TRANSPARENT) a = MIN_TRANSPARENT;

	pItem->m_clr = Color(a, r, g, b);
	pItem->nPenWidth = nPenWidth;
}

VOID CAnnotDrawer::StartDraw(INT nX, INT nY)
{
	m_pCurrentItem = new CAnnotItem;
	if(m_pCurrentItem == NULL) return;

	InitItem(m_pCurrentItem);
	m_image.AddStroke(m_pCurrentItem);

	POINT pt = {nX, nY};
	m_pCurrentItem->m_arPoint.push_back(pt);
}

VOID CAnnotDrawer::MoveDraw(INT nX, INT nY)
{
	if(m_pCurrentItem == NULL) return;

	POINT pt = {nX, nY};
	m_pCurrentItem->m_arPoint.push_back(pt);

	m_image.UpdateLayeredContent(m_hWndCanvas);
}

VOID CAnnotDrawer::EndDraw(INT nX, INT nY)
{
	if(m_pCurrentItem == NULL) return;

	POINT pt = {nX, nY};
	m_pCurrentItem->m_arPoint.push_back(pt);

	m_image.UpdateLayeredContent(m_hWndCanvas);

	m_pCurrentItem = NULL;
}
