// WebcamDirectShowDlg.cpp : 
// *** orgler electronics "Bozen South Tyrol Italy" *** 

#include "stdafx.h"
#include "WebcamDirectShow.h"
#include "DlgWebcam.h"

#include "CaptureGraph.h"
#include "Win2Dlg.h"
#include "MainDlg.h"

#pragma comment(lib, "strmiids")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString strInfo[10];   // Infos into our Listbox
int iIndex=0;
char cErrorList[2000];
char *ptrErrorList;

int iStep;

WINDOWPLACEMENT pwpWinWebcam;


//========================= dlgWin2 =============
extern int iArrOutput;
int iFlagGrabImage=0;
extern int iFlagLeftRight;

#define ImageX 640  
#define ImageY 480
//#define ImageX 1024  
//#define ImageY 768

unsigned char arrImage1 [4 * ImageX * ImageY];	
unsigned char arrImage2 [4 * ImageX * ImageY];	
unsigned char arrImage3 [4 * ImageX * ImageY];	


BITMAPINFO	bmpinfo;
CBitmap capture_map; 
int iBitmapFlag=0;

CWin2Dlg  dlgWin2;   // like a pointer to CWin2Dlg class
CMainDlg  dlgMain;
extern CRect RectWin2;
//=====================================================

HWND ghwndApp			=0; 
IMyCaptureGraphBuilder	*pBuilder;


struct _capstuff
{
    IVideoWindow			*pVW;
    IMediaEventEx			*pME;
    IAMVideoCompression		*pVC;
    IAMStreamConfig			*pVSC;      
    IBaseFilter				*pRender;
    IBaseFilter				*pVCap; 
    IGraphBuilder			*pFg;
    IMoniker				*rgpmVideoMenu[5];
    IMoniker				*pmVideo;
    BOOL					fCaptureGraphBuilt;
    BOOL fPreviewGraphBuilt;
    BOOL fCapturing;
    BOOL fPreviewing;
    WCHAR wachFriendlyName[120];
    double FrameRate;
	BOOL fUseFrameRate;
    BOOL fPreviewFaked;     
    int iNumVCapDevices;    // number of devices 
}gcap;




CWebcamDirectShowDlg::CWebcamDirectShowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWebcamDirectShowDlg::IDD, pParent)
{
	bmpinfo.bmiHeader.biSize		= sizeof(BITMAPINFOHEADER);
    bmpinfo.bmiHeader.biWidth		= ImageX;
    bmpinfo.bmiHeader.biHeight		= ImageY;
    bmpinfo.bmiHeader.biPlanes		= 1;
    bmpinfo.bmiHeader.biBitCount		= 32;
    bmpinfo.bmiHeader.biCompression		= BI_RGB;
    bmpinfo.bmiHeader.biSizeImage		= 0;
    bmpinfo.bmiHeader.biXPelsPerMeter	= 0;
    bmpinfo.bmiHeader.biYPelsPerMeter	= 0;
    bmpinfo.bmiHeader.biClrUsed			= 0;
    bmpinfo.bmiHeader.biClrImportant	= 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWebcamDirectShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DEVICES, m_ctrlListDevices);
}

BEGIN_MESSAGE_MAP(CWebcamDirectShowDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUT_SELECT_SOURCE, &CWebcamDirectShowDlg::OnBnClickedButSelectSource)
	ON_BN_CLICKED(IDC_BUT_GRAB_IMAGE, &CWebcamDirectShowDlg::OnBnClickedButGrabImage)
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()


void CWebcamDirectShowDlg::OnClose() 
{
	KillTimer(1);
	StopPreview();
    TearDownGraph();
    FreeCapFilters();

    // Store current settings in win.ini for next time
    TCHAR szBuf[512];
	ZeroMemory(szBuf,sizeof(szBuf));
	int ii=0;
 
	WCHAR *wszDisplayName = NULL;
	wszDisplayName = 0;

    if(gcap.pmVideo)
    {
     if(SUCCEEDED(gcap.pmVideo->GetDisplayName(0, 0, &wszDisplayName)))
          {
            if(wszDisplayName)
            {
			while(ii < 512) {szBuf[ii] = (TCHAR) wszDisplayName[ii]; ii++;}
            CoTaskMemFree(wszDisplayName);
            }
        }
    }

    // Save the current video device string
    WriteProfileString(TEXT("MyWEBCAM"), TEXT("VideoDevice2"), szBuf);

	CDialog::OnClose();
}


BOOL CWebcamDirectShowDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);
	
	//=============================================
	m_ctrlListDevices.ResetContent();
	gcap.iNumVCapDevices =  EnumerateAllDevices();
        	
	int ii=0;
	while(ii < gcap.iNumVCapDevices) m_ctrlListDevices.AddString(strInfo[ii++]);


	//=============================================
	ghwndApp = this->m_hWnd;
	gcap.FrameRate = 15.0;
    gcap.pmVideo   = 0;
	
	//========================================================

    TCHAR szVideoDisplayName[1024];
	ZeroMemory(szVideoDisplayName,sizeof(szVideoDisplayName));
    GetProfileString(TEXT("MyWEBCAM"), TEXT("VideoDevice2"), TEXT(""),szVideoDisplayName, NUMELMS(szVideoDisplayName));


	WCHAR wszVideo[1024];
	ZeroMemory(wszVideo,sizeof(wszVideo));
	ii=0; 
	while(szVideoDisplayName[ii] != 0) {   wszVideo[ii]=  szVideoDisplayName[ii]; ii++; }

    IBindCtx *lpBC    = 0;
	IMoniker *pmVideo = 0;
 
    HRESULT hr = CreateBindCtx(0, &lpBC);
    if(SUCCEEDED(hr))
    {
        DWORD dwEaten;
        hr = MkParseDisplayName(lpBC, wszVideo, &dwEaten, &pmVideo);
        lpBC->Release();
    }

   StartThisDevice(pmVideo);  
   
    //==== create and shows the second dialog window =========
	dlgWin2.Create(IDD_WIN2,this);
	dlgWin2.ShowWindow(SW_SHOW);
	//========================================================
	dlgMain.Create(IDD_MAIN_DIALOG, this);
	dlgMain.ShowWindow(SW_SHOW);

	IMonRelease(pmVideo);

	SetTimer(1,40,0);
	return TRUE;
 }


void CWebcamDirectShowDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); 

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}
HCURSOR CWebcamDirectShowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





BOOL InitCapFilters()
{
    HRESULT hr=S_OK;

    if(pBuilder)    return TRUE;

	//====================== STEP_05 ==============================

    pBuilder = new IMyCaptureGraphBuilder();
    if(pBuilder == NULL )
    {
		strInfo[iIndex++].Format("Cannot instantiate graph builder");
        return FALSE;
    }

     gcap.pVCap = NULL;
	 int ii,xx=0;
	 CString strFriendlyName;

	
    if(gcap.pmVideo != 0)
    {
        IPropertyBag *pBag;
        gcap.wachFriendlyName[0] = 0;

        hr = gcap.pmVideo->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
        if(SUCCEEDED(hr))
        {
            VARIANT var;
            var.vt = VT_BSTR;

            hr = pBag->Read(L"FriendlyName", &var, NULL);
            if(hr == NOERROR)
            {
             strFriendlyName.Format("%s",var.bstrVal);
			 ii = strFriendlyName.GetLength();
			 while(xx < ii) {gcap.wachFriendlyName[xx]= (WCHAR) strFriendlyName.GetAt(xx); xx++;}
             SysFreeString(var.bstrVal);
            }
            pBag->Release();
        }
        gcap.pmVideo->BindToObject(0, 0, IID_IBaseFilter, (void**)&gcap.pVCap);
    }

    if(gcap.pVCap == NULL)
    {
     strInfo[iIndex++].Format(TEXT("Error %x: Cannot create video capture filter"), hr);
     goto INIT_FILTERS_FAIL;
    }
  
    if(gcap.pFg) return TRUE;

    hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC,IID_IGraphBuilder, (LPVOID *)&gcap.pFg);

    hr = pBuilder->SetFiltergraph(gcap.pFg);
    if(hr != NOERROR)
    {
    strInfo[iIndex++].Format(TEXT("Cannot give graph to builder"));
    goto INIT_FILTERS_FAIL;
    }

    // Add the video capture filter to the graph with its friendly name
    hr = gcap.pFg->AddFilter(gcap.pVCap, gcap.wachFriendlyName);
    if(hr != NOERROR)
    {
    strInfo[iIndex++].Format(TEXT("Error %x: Cannot add vidcap to filtergraph"), hr);
    goto INIT_FILTERS_FAIL;
    }

       
    hr = pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,&MEDIATYPE_Video, gcap.pVCap,
                                          IID_IAMStreamConfig, (void **)&gcap.pVSC);
  	if(hr == S_OK)  return TRUE;


INIT_FILTERS_FAIL:
    FreeCapFilters();
    return FALSE;
}

void FreeCapFilters()
{
    SAFE_RELEASE(gcap.pFg);
    if( pBuilder )
    {
        delete pBuilder;
        pBuilder = NULL;
    }
    SAFE_RELEASE(gcap.pVCap);
    SAFE_RELEASE(gcap.pVSC);
    SAFE_RELEASE(gcap.pVC);
}


void TearDownGraph()
{
    SAFE_RELEASE(gcap.pRender);
    SAFE_RELEASE(gcap.pME);
    if(gcap.pVW)
    {
        // stop drawing in our window
        gcap.pVW->put_Owner(NULL);
        gcap.pVW->put_Visible(OAFALSE);
        gcap.pVW->Release();
        gcap.pVW = NULL;
    }

    if(gcap.pVCap)
        pBuilder->ReleaseFilters();

    gcap.fCaptureGraphBuilt = FALSE;
    gcap.fPreviewGraphBuilt = FALSE;
}



BOOL BuildPreviewGraph()
{
    int cy, cyBorder;
    HRESULT hr;
 			
            // maybe it's DV?
            hr = pBuilder->RenderStream(&PIN_CATEGORY_PREVIEW,&MEDIATYPE_Video, gcap.pVCap, NULL, NULL);
            if(hr == VFW_S_NOPREVIEWPIN)
            {
                // preview was faked up for us using the (only) capture pin
                gcap.fPreviewFaked = TRUE;
            }
            else if(hr != S_OK)
            {
                strInfo[iIndex++].Format(TEXT("!!! This graph cannot preview !!!"));
                gcap.fPreviewGraphBuilt = FALSE;
                return FALSE;
            }


  
    hr = gcap.pFg->QueryInterface(IID_IVideoWindow, (void **)&gcap.pVW);
    if(hr != NOERROR)
    {
        strInfo[iIndex++].Format(TEXT("!!! This graph cannot preview properly !!!"));
    }
    else
    {
        RECT rc;
        gcap.pVW->put_Owner((OAHWND)ghwndApp);    // We own the window now
        gcap.pVW->put_WindowStyle(WS_CHILD);      // you are now a child

        // give the preview window all our space but where the status bar is
        GetClientRect(ghwndApp, &rc);
        cyBorder = GetSystemMetrics(SM_CYBORDER);
        cy = 150 + cyBorder;
        rc.bottom -= cy;

    //   gcap.pVW->SetWindowPosition(0, 0, rc.right, rc.bottom); // be this big
    //  gcap.pVW->put_Visible(OATRUE);   // OATRUE = -1
	  gcap.pVW->SetWindowPosition(0, 0, ImageX, ImageY); // 
	  gcap.pVW->put_Visible(-1);
    }


    gcap.fPreviewGraphBuilt = TRUE;
    return TRUE;
}



BOOL StartPreview()
{
    if(gcap.fPreviewing)			 return TRUE;

    if(!gcap.fPreviewGraphBuilt)     return FALSE;

    // run the graph
    IMediaControl *pMC = NULL;
    HRESULT hr = gcap.pFg->QueryInterface(IID_IMediaControl, (void **)&pMC);
    if(SUCCEEDED(hr))
    {
        hr = pMC->Run();
        if(FAILED(hr))
        {
           pMC->Stop();
        }
        pMC->Release();
    }
    if(FAILED(hr))
    {
        strInfo[iIndex++].Format(TEXT("Error %x: Cannot run preview graph"), hr);
        return FALSE;
    }

    gcap.fPreviewing = TRUE;
    return TRUE;
}



BOOL StopPreview()
{
    if(!gcap.fPreviewing)  return FALSE;
 
    // stop the graph
    IMediaControl *pMC = NULL;
    HRESULT hr = gcap.pFg->QueryInterface(IID_IMediaControl, (void **)&pMC);
    if(SUCCEEDED(hr))
    {
        hr = pMC->Stop();
        pMC->Release();
    }
    if(FAILED(hr))
    {
        strInfo[iIndex++].Format(TEXT("Error %x: Cannot stop preview graph"), hr);
        return FALSE;
    }

    gcap.fPreviewing = FALSE;
    return TRUE;
}

//======================================================================================

void CWebcamDirectShowDlg::OnBnClickedButSelectSource()
{
  int ii = m_ctrlListDevices.GetCurSel();

   StartThisDevice(gcap.rgpmVideoMenu[ii]);	
}




void CWebcamDirectShowDlg::OnBnClickedButGrabImage()
{
	CopyImageFromWindow();
}



void CWebcamDirectShowDlg::CopyImageFromWindow()
{
CDC *dc = GetDC(); 
CDC     capture_dc; 

if(iBitmapFlag==0) // create a Bitmap only once 
{
capture_map.CreateCompatibleBitmap( dc , ImageX, ImageY ); 
iBitmapFlag=1;
}

capture_dc.CreateCompatibleDC( dc ); 
capture_dc.SelectObject( &capture_map ); 
capture_dc.BitBlt( 0, 0, ImageX, ImageY, dc, 0, 0, SRCCOPY );  //copy image to bitmap 

	//======= copy the image from bitmap to memory (arrImage1)===============
	LPBYTE lpBits = arrImage1;   // pointer to arrImage1
    int xx,err;
	xx = GetDIBits(capture_dc, capture_map, 0, ImageY, lpBits, &bmpinfo, DIB_RGB_COLORS);
	if(xx == 0)   err = GetLastError(); // only for debug

	capture_dc.DeleteDC();
	ReleaseDC(dc);
}



void CWebcamDirectShowDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent != 1) { CDialog::OnTimer(nIDEvent); return; }

	switch (iStep)
	{
	case 0: break;

	case 10: CopyImageFromWindow();		
		     iStep++;  break;

	case 11: iArrOutput=1;
			 dlgWin2.CopyToOutArray();
			 dlgWin2.InvalidateRect(RectWin2,false);  // repaint WIN2 with arrImage2 
			 iStep++;  break;  

	default: iStep=0;
	}
}




int CWebcamDirectShowDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (GetWindowPlacement(&pwpWinWebcam))
	{
    	pwpWinWebcam.rcNormalPosition.left  = 650; 
		pwpWinWebcam.rcNormalPosition.right = pwpWinWebcam.rcNormalPosition.left + ImageX;
		//pwpWinWebcam.rcNormalPosition.right = pwpWinWebcam.rcNormalPosition.left + 1024;
	
		SetWindowPlacement(&pwpWinWebcam);
	}
	return 0;
}
