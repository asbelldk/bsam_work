
// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

// MFC�� ���� �κа� ���� ������ ��� �޽����� ���� ����⸦ �����մϴ�.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.


#include <afxdisp.h>        // MFC �ڵ�ȭ Ŭ�����Դϴ�.



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC�� ���� �� ��Ʈ�� ���� ����

////////////////

#include <d3d9.h>
#include <Windows.h>
#include <WindowsX.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <mferror.h>
#include <assert.h>
#include <d3dx9.h>
#include <ks.h>
#include <ksmedia.h>
#include <Dbt.h>
#include <tchar.h>
#include <strsafe.h>
#include <AclAPI.h>


template <class T> void SafeRelease(T **ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}

#define BREAK_ON_FAIL(value)            if(FAILED(value)) break;
#define BREAK_ON_NULL(value, newHr)     if(value == NULL) { hr = newHr; break; }

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


//#include "resource.h"
#include "Device.h"
#include "Preview.h"

////////////////



#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


