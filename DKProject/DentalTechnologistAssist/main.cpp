#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

// Include the v6 common controls in the manifest
#pragma comment(linker,                      \
    "\"/manifestdependency:type='Win32' "     \
    "name='Microsoft.Windows.Common-Controls' "\
    "version='6.0.0.0' "                        \
    "processorArchitecture='*' "                 \
    "publicKeyToken='6595b64144ccf1df' "          \
    "language='*'\"")


#include "Common.h"
#include "resource.h"

#pragma comment(lib,"mfplat.lib")
#pragma message("linking with Microsoft's Media Foundation mfplat library ...")
#pragma comment(lib,"mf.lib")
#pragma message("linking with Microsoft's Media Foundation mf library ...")
#pragma comment(lib,"mfreadwrite.lib")
#pragma message("linking with Microsoft's Media Foundation mfreadwrite library ...")
#pragma comment(lib,"mfuuid.lib")
#pragma message("linking with Microsoft's Media Foundation mfuuid library ...")
#pragma comment(lib,"d3d9.lib")
#pragma message("linking with Microsoft's DirectX 3D 9 library ...")
#pragma comment(lib,"shlwapi.lib")
#pragma message("linking with Microsoft's shlwapi library ...")
#pragma comment(lib,"D3dx9.lib")
#pragma message("linking with Microsoft's DirectX 3DX 9 library ...")
#pragma comment(lib,"Advapi32.lib")
#pragma message("linking with Microsoft's Advapi32 library ...")


//
// ChooseDeviceParam structure
//
// Holds an array of IMFActivate pointers that represent video
// capture devices.
//



struct ChooseDeviceParam
{
	IMFActivate **ppDevices;    // Array of IMFActivate pointers.
	UINT32      count;          // Number of elements in the array.
	UINT32      selection;      // Selected device, by array index.
};



BOOL    InitializeApplication();
BOOL    InitializeWindow(HWND *pHwnd);
void    CleanUp();
INT     MessageLoop(HWND hwnd);


INT_PTR CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void    ShowErrorMessage(PCWSTR format, HRESULT hr);

// Window message handlers
BOOL    OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void    OnClose(HWND hwnd);
void    OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void    OnSize(HWND hwnd, UINT state, int cx, int cy);
void    OnDeviceChange(HWND hwnd, DEV_BROADCAST_HDR *pHdr);

// Command handlers
void    OnChooseDevice(HWND hwnd, bool bPrompt);

// Global variables
CPreview    *mf_Preview = NULL;
HDEVNOTIFY  g_hdevnotify = NULL;


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[] = L"WebCam Capture";
/*  Make the window name into a global variable  */
TCHAR szWindowName[] = L"Snoopy's WMF Webcam Capture.";

int WINAPI WinMain(HINSTANCE hThisInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszArgument,
	int nCmdShow)
{
	HWND hwnd = NULL;               /* This is the handle for our window */

	if (InitializeApplication() && InitializeWindow(&hwnd))
	{
		MessageLoop(hwnd);
	}

	CleanUp();


	/* The program return-value is 0 - The value that PostQuitMessage() gave */
	return 0;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)                  /* handle the messages */
	{
		HANDLE_MSG(hwnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hwnd, WM_CLOSE, OnClose);
		HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hwnd, WM_SIZE, OnSize);

	case WM_APP_PREVIEW_ERROR:
		ShowErrorMessage(L"Error", (HRESULT)wParam);
		break;

	case WM_DEVICECHANGE:
		OnDeviceChange(hwnd, (PDEV_BROADCAST_HDR)lParam);
		break;

	case WM_ERASEBKGND:
		return 1;

	default:                      /* for messages that we don't deal with */
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}

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

//-------------------------------------------------------------------
// CleanUp
//
// Releases resources.
//-------------------------------------------------------------------

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


//-------------------------------------------------------------------
// InitializeWindow
//
// Creates the application window.
//-------------------------------------------------------------------

BOOL InitializeWindow(HWND *pHwnd)
{
	WNDCLASS wc = { 0 };

	wc.lpfnWndProc = WindowProcedure;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = szClassName;
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

	if (!RegisterClass(&wc))
	{
		return FALSE;
	}

	HWND hwnd = CreateWindow(
		szClassName,
		szWindowName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if (!hwnd)
	{
		return FALSE;
	}

	ShowWindow(hwnd, SW_SHOWDEFAULT);
	UpdateWindow(hwnd);

	*pHwnd = hwnd;

	return TRUE;
}


//-------------------------------------------------------------------
// MessageLoop 
//
// Implements the window message loop.
//-------------------------------------------------------------------

INT MessageLoop(HWND hwnd)
{
	MSG msg = { 0 };

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	DestroyWindow(hwnd);

	return INT(msg.wParam);
}


//-------------------------------------------------------------------
// OnCreate
//
// Handles the WM_CREATE message.
//-------------------------------------------------------------------

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT)
{
	HRESULT hr = S_OK;
	SetSecurityInfo(GetModuleHandle(NULL), SE_FILE_OBJECT, OWNER_SECURITY_INFORMATION, NULL, NULL, NULL, NULL);
	// Register this window to get device notification messages.

	DEV_BROADCAST_DEVICEINTERFACE di = { 0 };
	di.dbcc_size = sizeof(di);
	di.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	di.dbcc_classguid = KSCATEGORY_CAPTURE;

	g_hdevnotify = RegisterDeviceNotification(
		hwnd,
		&di,
		DEVICE_NOTIFY_WINDOW_HANDLE
	);

	if (g_hdevnotify == NULL)
	{
		ShowErrorMessage(L"RegisterDeviceNotification failed.", HRESULT_FROM_WIN32(GetLastError()));
		return FALSE;
	}

	// Create the object that manages video preview. 
	hr = CPreview::CreateInstance(hwnd, hwnd, &mf_Preview);

	if (FAILED(hr))
	{
		ShowErrorMessage(L"CPreview::CreateInstance failed.", hr);
		CleanUp();
		return FALSE;
	}

	// Select the first available device (if any).
	OnChooseDevice(hwnd, true);
	SetWindowPos(hwnd, HWND_TOP, 0, 0, mf_Preview->m_draw.width, mf_Preview->m_draw.height, NULL);
	return TRUE;
}



//-------------------------------------------------------------------
// OnClose
//
// Handles WM_CLOSE messages.
//-------------------------------------------------------------------

void OnClose(HWND /*hwnd*/)
{
	CleanUp();
	PostQuitMessage(0);
}



//-------------------------------------------------------------------
// OnSize
//
// Handles WM_SIZE messages.
//-------------------------------------------------------------------

void OnSize(HWND hwnd, UINT /*state */, int cx, int cy)
{
	if (mf_Preview)
	{
		mf_Preview->ResizeVideo((WORD)cx, (WORD)cy);

		InvalidateRect(hwnd, NULL, FALSE);
	}
}


//-------------------------------------------------------------------
// OnCommand 
//
// Handles WM_COMMAND messages
//-------------------------------------------------------------------

void OnCommand(HWND hwnd, int id, HWND /*hwndCtl*/, UINT /*codeNotify*/)
{
	switch (id)
	{
	case ID_FILE_CHOOSEDEVICE:
		OnChooseDevice(hwnd, TRUE);
		break;

	case ID_FILE_CAPTURE:
		mf_Preview->m_draw.saveframe = true;
		break;
	}
}

//-------------------------------------------------------------------
//  OnChooseDevice
//
//  Select a video capture device.
//
//  hwnd:    A handle to the application window.
/// bPrompt: If TRUE, prompt to user to select the device. Otherwise,
//           select the first device in the list.
//-------------------------------------------------------------------

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
		MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID
	);

	if (FAILED(hr)) { CleanUp(); }

	// Enumerate devices.
	hr = MFEnumDeviceSources(pAttributes, &param.ppDevices, &param.count);

	if (FAILED(hr)) { CleanUp(); }

	// NOTE: param.count might be zero.

	if (bPrompt)
	{
		// Ask the user to select a device.

		INT_PTR result = DialogBoxParam(
			GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDD_CHOOSE_DEVICE),
			hwnd,
			DlgProc,
			(LPARAM)& param
		);

		if (result == IDOK)
		{
			iDevice = param.selection;
		}
		else
		{
			bCancel = true; // User cancelled
			PostQuitMessage(0);
		}
	}

	if (!bCancel && (param.count > 0))
	{
		// Give this source to the CPlayer object for preview.
		hr = mf_Preview->SetDevice(param.ppDevices[iDevice]);
		if (FAILED(hr))
		{
			ShowErrorMessage(L"Cannot create a video capture device", hr);
			SafeRelease(&pAttributes);

			for (DWORD i = 0; i < param.count; i++)
			{
				SafeRelease(&param.ppDevices[i]);
			}
			CoTaskMemFree(param.ppDevices);
		}


	}
	else
	{

		CleanUp();
		hr = -1;
	}
	SetWindowPos(hwnd, HWND_TOP, 0, 0, mf_Preview->m_draw.m_width - 60, mf_Preview->m_draw.m_height, SWP_SHOWWINDOW);



	SafeRelease(&pAttributes);

	for (DWORD i = 0; i < param.count; i++)
	{
		SafeRelease(&param.ppDevices[i]);
	}
	CoTaskMemFree(param.ppDevices);

	if (FAILED(hr))
	{
		ShowErrorMessage(L"Cannot create a video capture device", hr);
	}
}


//-------------------------------------------------------------------
//  OnDeviceChange
//
//  Handles WM_DEVICECHANGE messages.
//-------------------------------------------------------------------

void OnDeviceChange(HWND hwnd, DEV_BROADCAST_HDR *pHdr)
{
	if (mf_Preview == NULL || pHdr == NULL)
	{
		return;
	}

	HRESULT hr = S_OK;
	BOOL bDeviceLost = FALSE;

	// Check if the current device was lost.

	hr = mf_Preview->CheckDeviceLost(pHdr, &bDeviceLost);

	if (FAILED(hr) || bDeviceLost)
	{
		mf_Preview->CloseDevice();

		MessageBox(hwnd, L"Lost the capture device.", szWindowName, MB_OK);
	}
}


/////////////////////////////////////////////////////////////////////

// Dialog functions

void    OnInitDialog(HWND hwnd, ChooseDeviceParam *pParam);
HRESULT OnOK(HWND hwnd, ChooseDeviceParam *pParam);

//-------------------------------------------------------------------
//  DlgProc
//
//  Dialog procedure for the "Select Device" dialog.
//-------------------------------------------------------------------

INT_PTR CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static ChooseDeviceParam *pParam = NULL;

	switch (msg)
	{
	case WM_INITDIALOG:
		pParam = (ChooseDeviceParam*)lParam;
		OnInitDialog(hwnd, pParam);
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			OnOK(hwnd, pParam);
			EndDialog(hwnd, LOWORD(wParam));
			return TRUE;

		case IDCANCEL:
			EndDialog(hwnd, LOWORD(wParam));
			return TRUE;
		}
		break;
	}

	return FALSE;
}


//-------------------------------------------------------------------
//  OnInitDialog
//
//  Handles the WM_INITDIALOG message.
//-------------------------------------------------------------------

void OnInitDialog(HWND hwnd, ChooseDeviceParam *pParam)
{
	HRESULT hr = S_OK;

	// Populate the list with the friendly names of the devices.

	HWND hList = GetDlgItem(hwnd, IDC_DEVICE_LIST);

	for (DWORD i = 0; i < pParam->count; i++)
	{
		WCHAR *szFriendlyName = NULL;

		hr = pParam->ppDevices[i]->GetAllocatedString(
			MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME,
			&szFriendlyName,
			NULL
		);

		if (FAILED(hr))
		{
			break;
		}


		int index = ListBox_AddString(hList, szFriendlyName);

		ListBox_SetItemData(hList, index, i);

		CoTaskMemFree(szFriendlyName);
	}

	// Assume no selection for now.
	pParam->selection = (UINT32)-1;

	if (pParam->count == 0)
	{
		// If there are no devices, disable the "OK" button.
		EnableWindow(GetDlgItem(hwnd, IDOK), FALSE);
	}
}


HRESULT OnOK(HWND hwnd, ChooseDeviceParam *pParam)
{
	HWND hList = GetDlgItem(hwnd, IDC_DEVICE_LIST);

	int sel = ListBox_GetCurSel(hList);

	if (sel != LB_ERR)
	{
		pParam->selection = (UINT32)ListBox_GetItemData(hList, sel);
	}

	return S_OK;
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