
// Tool2.h : Tool2 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CTool2App:
// �� Ŭ������ ������ ���ؼ��� Tool2.cpp�� �����Ͻʽÿ�.
//

class CTool2App : public CWinApp
{
public:
	CTool2App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTool2App theApp;
