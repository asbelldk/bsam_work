#include "stdafx.h"
#include "WebcamDirectShow.h"
#include "DlgWebcam.h"

#include "MainDlg.h"
#include <direct.h>

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

#define ImageX 640
#define ImageY 480
//#define ImageX 1024
//#define ImageY 768

extern unsigned char arrImage1[4 * ImageX * ImageY];
//extern unsigned char arrImage2[4 * ImageX * ImageY];
//extern unsigned char arrImage3[4 * ImageX * ImageY];
//
//int iArrOutput = 1;							// default from take a picture 
//unsigned char *ptrArrInput, *ptrArrOutput;
//unsigned char *ptrImage = arrImage1;			// default wert
//
//
//extern BITMAPINFO	bmpinfo;
//extern int iStep;
//extern int iFlagExpanded;
//
//int rectFlag;
//CRect RectWin2;
//extern CRect RectWin2;
//
//
//WINDOWPLACEMENT pwpWin2;

IMPLEMENT_DYNAMIC(CMainDlg, CDialog)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
	//, b_checkgreyed(FALSE)
{
}

CMainDlg::~CMainDlg()
{
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Check(pDX, IDC_CHECK_GRAY, b_checkgreyed);

}


BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_CREATE()	
END_MESSAGE_MAP()



//========================== ppp ========================================
void CMainDlg::OnPaint()
{
	CPaintDC dc(this);		// device context for painting

							//===============================================
	//if (rectFlag == 0)
	//{
	//	GetClientRect(&RectWin2);
	//	rectFlag = 1;
	//}

	//switch (iArrOutput)
	//{
	//case 1: ptrImage = arrImage1;   break;
	//case 2: ptrImage = arrImage2;   break;
	//case 3: ptrImage = arrImage3;   break;
	//}

	//// copy memory arrImage2 to window 
	//SetDIBitsToDevice((HDC)dc, 0, 0, ImageX, ImageY, 0, 0, 0, ImageX, ptrImage, &bmpinfo, DIB_RGB_COLORS);
}

int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	/*if (GetWindowPlacement(&pwpWin2))
	{
		pwpWin2.rcNormalPosition.left = 0;
		pwpWin2.rcNormalPosition.right = pwpWin2.rcNormalPosition.left + ImageX;

		SetWindowPlacement(&pwpWin2);
	}*/
	return 0;
}


//BITMAPINFO	bmpOutInfo;
//CBitmap     bitmapOut;

//void CMainDlg::OnBnClickedButSaveBmp()
//{
//	bmpOutInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
//	bmpOutInfo.bmiHeader.biWidth = ImageX;
//	bmpOutInfo.bmiHeader.biHeight = ImageY;
//	bmpOutInfo.bmiHeader.biPlanes = 1;
//	bmpOutInfo.bmiHeader.biBitCount = 32;
//	bmpOutInfo.bmiHeader.biCompression = BI_RGB;
//	bmpOutInfo.bmiHeader.biSizeImage = 0;
//	bmpOutInfo.bmiHeader.biXPelsPerMeter = 0;
//	bmpOutInfo.bmiHeader.biYPelsPerMeter = 0;
//	bmpOutInfo.bmiHeader.biClrUsed = 0;
//	bmpOutInfo.bmiHeader.biClrImportant = 0;
//
//
//	switch (iArrOutput)
//	{
//	case 1: ptrImage = arrImage1;   break;
//	case 2: ptrImage = arrImage2;   break;
//	case 3: ptrImage = arrImage3;   break;
//	}
//
//	char dirBuffer1[512];
//	memset(dirBuffer1, 0, sizeof(dirBuffer1));
//	_getcwd(dirBuffer1, sizeof(dirBuffer1));
//	char cPath[1024];
//	sprintf(cPath, "%s\\test.bmp", dirBuffer1);
//	HRESULT hr = BitmapSaveToFile(cPath, &bmpOutInfo, sizeof(BITMAPINFOHEADER), ptrImage, sizeof(arrImage2));
//}
//
//
//
//
//HRESULT CWin2Dlg::BitmapSaveToFile(char *pFileName, BITMAPINFO *pBMI, size_t cbBMI, BYTE *pData, size_t cbData)
//{
//	HANDLE hFile = CreateFile(pFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
//	if (hFile == NULL)
//	{
//		return HRESULT_FROM_WIN32(GetLastError());
//	}
//
//	BITMAPFILEHEADER bmf = {};
//	bmf.bfType = 'MB';
//	bmf.bfSize = cbBMI + cbData + sizeof(bmf);
//
//	bmf.bfOffBits = sizeof(bmf) + cbBMI;
//
//	DWORD cbWritten = 0;
//	BOOL result = WriteFile(hFile, &bmf, sizeof(bmf), &cbWritten, NULL);
//	if (result)
//	{
//		result = WriteFile(hFile, pBMI, cbBMI, &cbWritten, NULL);
//	}
//	if (result)
//	{
//		result = WriteFile(hFile, pData, cbData, &cbWritten, NULL);
//	}
//
//	HRESULT hr = result ? S_OK : HRESULT_FROM_WIN32(GetLastError());
//
//	CloseHandle(hFile);
//
//	return hr;
//}
//
//
//
//
//
//void CWin2Dlg::OnBnClickedButTakePicture() { iStep = 10; }
//
//void CWin2Dlg::OnBnClickedCheckGray() { CalcNew(); }
//
//void CWin2Dlg::OnBnClickedCheckLeftRight() { CalcNew(); }
//
//void CWin2Dlg::OnBnClickedCheckFilter() { CalcNew(); }
//
//void CWin2Dlg::OnBnClickedCheckFilter2() { CalcNew(); }
//
//void CWin2Dlg::CalcNew(void)
//{
//	UpdateData(true);
//	CopyToOutArray();
//
//	InvalidateRect(RectWin2, false); // repaint WIN2  with arrImage2	
//}
//
//
//
//
//
//
//void CWin2Dlg::CopyToOutArray(void)
//{
//	int iLine, iCol;
//
//	int iOffsetOneLine = ImageX * 4;
//	int iOffset = 0;
//
//	unsigned char *ptrArr1, *ptrArr2;
//
//
//	switch (iArrOutput)
//	{
//	case 1:  ptrArrInput = arrImage1;   ptrArrOutput = arrImage2;   iArrOutput = 2; break;
//	case 2:  ptrArrInput = arrImage2;   ptrArrOutput = arrImage3;   iArrOutput = 3; break;
//	case 3:  ptrArrInput = arrImage3;   ptrArrOutput = arrImage2;   iArrOutput = 2; break;
//	default: ptrArrInput = arrImage1;   ptrArrOutput = arrImage2;   iArrOutput = 2; break;
//	}
//
//	if (b_checkleftright == false)
//	{
//		iLine = 0;
//		while (iLine < ImageY)
//		{
//			iCol = 0;
//			while (iCol < ImageX)
//			{
//				iOffset = (iLine * iOffsetOneLine + iCol * 4);
//				ptrArr1 = ptrArrInput + iOffset;
//				ptrArr2 = ptrArrOutput + iOffset;
//
//				*ptrArr2++ = *ptrArr1++;
//				*ptrArr2++ = *ptrArr1++;
//				*ptrArr2++ = *ptrArr1++;
//				iCol++;
//			}
//			iLine++;
//		}// end iLine		
//	}// == 0
//
//
//	if (b_checkleftright == TRUE)
//	{
//		iLine = 0;
//		while (iLine < ImageY)
//		{
//			iCol = 0;
//			while (iCol < ImageX)
//			{
//				iOffset = (iLine * iOffsetOneLine + iCol * 4);
//				ptrArr1 = ptrArrInput;  	ptrArr1 += iOffset;
//				ptrArr2 = ptrArrOutput;  	ptrArr2 += (iLine * iOffsetOneLine + iOffsetOneLine - iCol * 4 + 4);
//				*ptrArr2++ = *ptrArr1++;
//				*ptrArr2++ = *ptrArr1++;
//				*ptrArr2++ = *ptrArr1++;
//
//				iCol++;
//			}
//			iLine++;
//		}
//	}
//	//====================================================
//
//	unsigned char cRed, cGreen, cBlue;
//	int iGrayRed, iGrayGreen, iGrayBlue;
//	int iGraySum;
//	unsigned char cGray;
//
//
//	if (b_checkgreyed)
//	{
//		iLine = 0;
//		while (iLine < ImageY)
//		{
//			iCol = 0;
//			while (iCol < ImageX)
//			{
//				iOffset = (iLine * iOffsetOneLine + iCol * 4);
//				ptrArr2 = ptrArrOutput;  	ptrArr2 += iOffset;
//
//				cBlue = *ptrArr2;
//				cGreen = *(ptrArr2 + 1);
//				cRed = *(ptrArr2 + 2);
//				// cRed  =0;   // for test
//				// cGreen=0;
//				// cBlue =0;
//				iGrayBlue = cBlue * 29;
//				iGrayGreen = cGreen * 152;
//				iGrayRed = cRed * 77;
//				iGraySum = iGrayBlue + iGrayGreen + iGrayRed;
//				iGraySum /= 256;
//				cGray = (unsigned char)iGraySum;
//
//				*ptrArr2++ = cGray;
//				*ptrArr2++ = cGray;
//				*ptrArr2++ = cGray;
//
//				iCol++;
//			}
//			iLine++;
//		}// end iLine		
//	}// end grayed
//
//}
//
//
//void CWin2Dlg::OnBnClickedButLeftRight()
//{
//
//	int iLine, iCol;
//	int iOffsetOneLine = ImageX * 4;
//	int iOffset = 0;
//	unsigned char *ptrArr1, *ptrArr2;
//
//
//	switch (iArrOutput)
//	{
//	case 1:  ptrArrInput = arrImage1;   ptrArrOutput = arrImage2;   iArrOutput = 2; break;
//	case 2:  ptrArrInput = arrImage2;   ptrArrOutput = arrImage3;   iArrOutput = 3; break;
//	case 3:  ptrArrInput = arrImage3;   ptrArrOutput = arrImage2;   iArrOutput = 2; break;
//	default: ptrArrInput = arrImage1;   ptrArrOutput = arrImage2;   iArrOutput = 2; break;
//	}
//
//	iLine = 0;
//	while (iLine < ImageY)
//	{
//		iCol = 0;
//		while (iCol < ImageX)
//		{
//			iOffset = (iLine * iOffsetOneLine + iCol * 4);
//			ptrArr1 = ptrArrInput;  	ptrArr1 += iOffset;
//			ptrArr2 = ptrArrOutput;  	ptrArr2 += (iLine * iOffsetOneLine + iOffsetOneLine - iCol * 4 + 4);
//			*ptrArr2++ = *ptrArr1++;
//			*ptrArr2++ = *ptrArr1++;
//			*ptrArr2++ = *ptrArr1++;
//
//			iCol++;
//		}
//		iLine++;
//	}
//
//	InvalidateRect(RectWin2, false); // repaint WIN2  with arrImage2	
//}
//
//
//
//
//
//void CWin2Dlg::SetInputOutput(void)
//{
//	switch (iArrOutput)
//	{
//	case 1:  ptrArrInput = arrImage1;   ptrArrOutput = arrImage2;   iArrOutput = 2; break;
//	case 2:  ptrArrInput = arrImage2;   ptrArrOutput = arrImage3;   iArrOutput = 3; break;
//	case 3:  ptrArrInput = arrImage3;   ptrArrOutput = arrImage2;   iArrOutput = 2; break;
//	default: ptrArrInput = arrImage1;   ptrArrOutput = arrImage2;   iArrOutput = 2; break;
//	}
//}