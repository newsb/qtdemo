#ifndef __ANNOT_IMAGE_H__
#define __ANNOT_IMAGE_H__

#include <Windows.h>
#include "gdiplus/GdiPlus.h"
#include "DibSection.h"
#include <vector>

struct CAnnotItem
{
	INT nPenWidth;
	Gdiplus::Color m_clr;

	std::vector<POINT> m_arPoint;
};

class CAnnotImage
{
public:
	CAnnotImage();
	~CAnnotImage();
	
	BOOL Initialize(HWND hWnd, INT nWidth, INT nHeight);
	VOID Destroy();

	VOID UpdateLayeredContent(HWND hWnd);

	VOID AddStroke(CAnnotItem* pItem);

private:
	VOID DrawItem(CAnnotItem* pItem);
	VOID DrawContent();

	VOID ClearData();
	VOID InitImage();

private:
	Gdiplus::Graphics* m_pGraphic;

	INT m_nWidth;
	INT m_nHeight;

	CDibSection m_dib;
	HDC m_hDC;
	HBITMAP m_hBmpOld;

	std::vector<CAnnotItem*> m_arData;
};


class CAnnotDrawer
{
public:
	CAnnotDrawer();
	~CAnnotDrawer();

	BOOL Initialize(HWND hWnd, INT nWidth, INT nHeight);
	VOID Destroy();

	VOID SetCanvas(HWND hWnd);

	VOID StartDraw(INT nX, INT nY);
	VOID MoveDraw(INT nX, INT nY);
	VOID EndDraw(INT nX, INT nY);

private:
	VOID InitItem(CAnnotItem* pItem);

private:
	CAnnotImage m_image;
	HWND m_hWndCanvas;
	CAnnotItem* m_pCurrentItem;
};

#endif //__ANNOT_IMAGE_H__