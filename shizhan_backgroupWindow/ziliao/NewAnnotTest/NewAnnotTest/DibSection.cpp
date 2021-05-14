#include "DibSection.h"

CDibSection::CDibSection()
:m_hBmp(NULL), m_pData(NULL)
{
	ZeroMemory(&m_bmi, sizeof(m_bmi));
}

CDibSection::~CDibSection()
{
	Destroy();
}

BOOL CDibSection::Create(HDC dc, INT nWidth, INT nHeight, INT nColorBits, BOOL bFlip)
{
	Destroy();

	if(nHeight < 0) nHeight = -nHeight;

	m_bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_bmi.bmiHeader.biWidth = nWidth;
	m_bmi.bmiHeader.biHeight= bFlip ? nHeight : -nHeight;
	m_bmi.bmiHeader.biPlanes = 1;
	m_bmi.bmiHeader.biBitCount = nColorBits;
	m_bmi.bmiHeader.biCompression = BI_RGB;

	HDC hdcDesktop = NULL;
	if(dc == NULL)
	{
		dc = hdcDesktop = GetDC(NULL);
	}

	m_hBmp = CreateDIBSection(dc, &m_bmi, DIB_RGB_COLORS, (LPVOID*)&m_pData, NULL, NULL);

	if(hdcDesktop != NULL)
	{
		ReleaseDC(NULL, hdcDesktop);
	}

	return m_hBmp != NULL;
}

VOID CDibSection::Destroy()
{
	if(m_hBmp != NULL)
	{
		DeleteObject(m_hBmp);
	}

	ZeroMemory(&m_bmi, sizeof(m_bmi));
	m_hBmp = NULL;
	m_pData = NULL;
}

BOOL CDibSection::IsNull() const 
{
	return m_hBmp == NULL;
}

HBITMAP CDibSection::Detach()
{
	HBITMAP hBmpRet(m_hBmp);
	m_hBmp = NULL;
	return hBmpRet;
}

HBITMAP CDibSection::GetBitmap() const
{
	return m_hBmp;
}

INT CDibSection::GetWidth() const
{
	return m_bmi.bmiHeader.biWidth;
}

INT CDibSection::GetHeight() const
{
	INT nHeight = m_bmi.bmiHeader.biHeight;
	if(nHeight < 0) nHeight = -nHeight;
	return nHeight;
}

LPBYTE CDibSection::GetRawData() const
{
	return m_pData;
}

INT CDibSection::GetLineBytes() const
{
	return (m_bmi.bmiHeader.biWidth * m_bmi.bmiHeader.biBitCount + 31) / 32 * 4;
}


