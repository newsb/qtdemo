#ifndef __DIB_SECTION_H__
#define __DIB_SECTION_H__

#include <Windows.h>
#include <tchar.h>

class CDibSection
{
public:
	CDibSection();
	~CDibSection();

	BOOL Create(HDC dc, INT nWidth, INT nHeight, INT nColorBits, BOOL bFlip = FALSE);
	VOID Destroy();

	BOOL IsNull() const;

	HBITMAP Detach();

	HBITMAP GetBitmap() const;
	INT GetWidth() const;
	INT GetHeight() const;
	LPBYTE GetRawData() const;
	INT GetLineBytes() const;

private:
	BITMAPINFO m_bmi;
	HBITMAP m_hBmp;
	LPBYTE m_pData;
};

#endif //__DIB_SECTION_H__