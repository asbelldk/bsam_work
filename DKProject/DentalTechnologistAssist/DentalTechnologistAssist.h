
// DentalTechnologistAssist.h : DentalTechnologistAssist ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CDentalTechnologistAssistApp:
// �� Ŭ������ ������ ���ؼ��� DentalTechnologistAssist.cpp�� �����Ͻʽÿ�.
//

class CDentalTechnologistAssistApp : public CWinAppEx
{
public:
	CDentalTechnologistAssistApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnIdle(LONG lCount);

// �����Դϴ�.
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDentalTechnologistAssistApp theApp;
