
// Tool3.h : Tool3 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CTool3App:
// �� Ŭ������ ������ ���ؼ��� Tool3.cpp�� �����Ͻʽÿ�.
//

class CTool3App : public CWinAppEx
{
public:
	CTool3App();

protected:
	CMultiDocTemplate* m_pDocTemplate;
public:

// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	afx_msg void OnFileNewFrame();
	afx_msg void OnFileNew();
	DECLARE_MESSAGE_MAP()
};

extern CTool3App theApp;
