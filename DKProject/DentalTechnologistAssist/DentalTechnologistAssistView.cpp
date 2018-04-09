
// DentalTechnologistAssistView.cpp : CDentalTechnologistAssistView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "DentalTechnologistAssist.h"
#endif

#include "DentalTechnologistAssistDoc.h"
#include "DentalTechnologistAssistView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


////////////////////////////////////////////////////////////////////////////////////////

///*  Make the window name into a global variable  */
TCHAR szWindowName[] = L"Snoopy's WMF Webcam Capture.";

// Global variables  
CPreview    *mf_Preview = NULL;
HDEVNOTIFY  g_hdevnotify = NULL;

struct ChooseDeviceParam
{
    IMFActivate **ppDevices;    // Array of IMFActivate pointers.  
    UINT32      count;          // Number of elements in the array.  
    UINT32      selection;      // Selected device, by array index.  
};

BOOL InitializeApplication()
{
	HRESULT hr = S_OK;
	hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr))
	{
	    hr = MFStartup(MF_VERSION);
	}	
	
	return (SUCCEEDED(hr));
}

void CleanUp()
{
	if (g_hdevnotify)
	{
		UnregisterDeviceNotification(g_hdevnotify);
	}

	if (mf_Preview)
	{
		mf_Preview->CloseDevice();
	}

	SafeRelease(&mf_Preview);
	MFShutdown();
	CoUninitialize();
}

void ShowErrorMessage(PCWSTR format, HRESULT hrErr)
{
	HRESULT hr = S_OK;
	WCHAR msg[MAX_PATH];
	hr = StringCbPrintf(msg, sizeof(msg), L"%s ", hrErr);
    if (SUCCEEDED(hr))
	{
		MessageBox(NULL, msg, L"Error", MB_OK);
	}
	else
	{
        DebugBreak();
    }
}

void OnChooseDevice(HWND hwnd, bool bPrompt)
{
	HRESULT hr = S_OK;
	ChooseDeviceParam param = { 0 };
    UINT iDevice = 0;   // Index into the array of devices  
	BOOL bCancel = FALSE;
    IMFAttributes *pAttributes = NULL;

    // Initialize an attribute store to specify enumeration parameters.
    hr = MFCreateAttributes(&pAttributes, 1);
    if (FAILED(hr)) { CleanUp(); }

    // Ask for source type = video capture devices.  
    hr = pAttributes->SetGUID(
         MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE,
         MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID);
    if (FAILED(hr)) { CleanUp(); }

	// Enumerate devices.
    hr = MFEnumDeviceSources(pAttributes, &param.ppDevices, &param.count);
    if (FAILED(hr)) { CleanUp(); }

    // NOTE: param.count might be zero.
 //   if (bPrompt)
 //   {
 //       // Ask the user to select a device.  
 //        INT_PTR result = DialogBoxParam(
 //            GetModuleHandle(NULL),
 //            MAKEINTRESOURCE(IDD_CHOOSE_DEVICE),
 //            hwnd,
 //            DlgProc,
 //            (LPARAM)& param);

	//	if (result == IDOK)
	//	{
	//		iDevice = param.selection;
	//	}
	//	else
	//	{
	//		bCancel = true; // User cancelled  
	//		PostQuitMessage(0);
	//	}
	//}

    if (!bCancel && (param.count > 0))
	//if(param.count > 0)
    {
        // Give this source to the CPlayer object for preview.
		hr = mf_Preview->SetDevice(param.ppDevices[iDevice]);
        if (FAILED(hr))
        {
			ShowErrorMessage(L"Cannot create a video capture device", hr);
			SafeRelease(&pAttributes);

	        for(DWORD i = 0; i < param.count; i++)
				SafeRelease(&param.ppDevices[i]);

			CoTaskMemFree(param.ppDevices);
		}
	}
	else
    {
	    //CleanUp();
        hr = -1;

		return;
    }

	SetWindowPos(hwnd, HWND_TOP, 0, 0, mf_Preview->m_draw.m_width - 60, mf_Preview->m_draw.m_height, SWP_SHOWWINDOW);
    SafeRelease(&pAttributes);

    for(DWORD i = 0; i < param.count; i++)
		SafeRelease(&param.ppDevices[i]);

	CoTaskMemFree(param.ppDevices);

    if(FAILED(hr))
	    ShowErrorMessage(L"Cannot create a video capture device", hr);
}

void OnDeviceChange(HWND hwnd, DEV_BROADCAST_HDR *pHdr)
{
	if(mf_Preview == NULL || pHdr == NULL)
	    return;

    HRESULT hr = S_OK;
	BOOL bDeviceLost = FALSE;

    // Check if the current device was lost.
    hr = mf_Preview->CheckDeviceLost(pHdr, &bDeviceLost);
    if(FAILED(hr) || bDeviceLost)
    {
		mf_Preview->CloseDevice();
		MessageBox(hwnd, L"Lost the capture device.", szWindowName, MB_OK);
    }
}

////////////////////////////////////////////////////////////////////////////////////////

// CDentalTechnologistAssistView

IMPLEMENT_DYNCREATE(CDentalTechnologistAssistView, CView)

BEGIN_MESSAGE_MAP(CDentalTechnologistAssistView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDentalTechnologistAssistView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_SIZE()
	//ON_WM_DRAW()
END_MESSAGE_MAP()

// CDentalTechnologistAssistView ����/�Ҹ�

int CDentalTechnologistAssistView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	/*if (CDentalTechnologistAssistView::OnCreate(lpCreateStruct) == -1)
		return -1;*/

	CWnd *pWnd = AfxGetMainWnd();
	HWND hWnd = pWnd->m_hWnd;

	HRESULT hr = S_OK;
	SetSecurityInfo(GetModuleHandle(NULL), SE_FILE_OBJECT, OWNER_SECURITY_INFORMATION, NULL, NULL, NULL, NULL);
	// Register this window to get device notification messages.  
	DEV_BROADCAST_DEVICEINTERFACE di = { 0 };
	di.dbcc_size = sizeof(di);
	di.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	di.dbcc_classguid = KSCATEGORY_CAPTURE;
	g_hdevnotify = RegisterDeviceNotification(hWnd, &di, DEVICE_NOTIFY_WINDOW_HANDLE);
	if (g_hdevnotify == NULL)
	{
	    ShowErrorMessage(L"RegisterDeviceNotification failed.", HRESULT_FROM_WIN32(GetLastError()));
	    return -1;
	}
    // Create the object that manages video preview.   
    hr = CPreview::CreateInstance(hWnd, hWnd, &mf_Preview);
    if (FAILED(hr))
	{
		ShowErrorMessage(L"CPreview::CreateInstance failed.", hr);
        CleanUp();

        return -1;
    }

    // Select the first available device (if any).  
    OnChooseDevice(hWnd, true);

	//SetWindowPos(hWnd, HWND_TOP, 0, 0, mf_Preview->m_draw.width, mf_Preview->m_draw.height, NULL);
	SetWindowPos(pWnd, 0, 0, mf_Preview->m_draw.width, mf_Preview->m_draw.height, NULL);

	return 0;
}

void CDentalTechnologistAssistView::OnClose()
{
	//CDentalTechnologistAssistView::OnClose();
	CleanUp();
}

void CDentalTechnologistAssistView::OnSize(UINT nType, int cx, int cy)
{
	//CDentalTechnologistAssistView::OnSize(nType, cx, cy);

	/*CWnd *pWnd = AfxGetMainWnd();
	HWND hWnd = pWnd->m_hWnd;

	if(mf_Preview)
	{
	    mf_Preview->ResizeVideo((WORD)cx, (WORD)cy);
		InvalidateRect(NULL, FALSE);
	}*/
}

CDentalTechnologistAssistView::CDentalTechnologistAssistView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CDentalTechnologistAssistView::~CDentalTechnologistAssistView()
{
}

BOOL CDentalTechnologistAssistView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CDentalTechnologistAssistView �׸���

void CDentalTechnologistAssistView::OnDraw(CDC* pDC)
{
	if(pDC == NULL) return;

	CString strText = _T("TODO: implement thumbnail drawing here");
	//pDC->FillSolidRect(lprcBounds, RGB(255, 255, 255));
	CRect rectClient;
	GetClientRect(rectClient);
	
	pDC->DrawText(strText, rectClient, DT_CENTER | DT_WORDBREAK);

	mf_Preview->m_draw.TestDraw();
	//mf_Preview->OnReadSample()
	//pDC->DrawText("dsadaeea", 8, &a, RGB(255, 0, 0));
	//CDentalTechnologistAssistDoc* pDoc = GetDocument();
	///ASSERT_VALID(pDoc);
	//if (!pDoc)
	//	return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CDentalTechnologistAssistView �μ�


void CDentalTechnologistAssistView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDentalTechnologistAssistView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CDentalTechnologistAssistView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CDentalTechnologistAssistView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CDentalTechnologistAssistView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDentalTechnologistAssistView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDentalTechnologistAssistView ����

#ifdef _DEBUG
void CDentalTechnologistAssistView::AssertValid() const
{
	CView::AssertValid();
}

void CDentalTechnologistAssistView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDentalTechnologistAssistDoc* CDentalTechnologistAssistView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDentalTechnologistAssistDoc)));
	return (CDentalTechnologistAssistDoc*)m_pDocument;
}
#endif //_DEBUG


// CDentalTechnologistAssistView �޽��� ó����