#pragma once


// CMainDlg
class CMainDlg : public CDialog
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);
	virtual ~CMainDlg();

	enum { IDD = IDD_MAIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg HCURSOR OnQueryDragIcon();
	//DECLARE_MESSAGE_MAP()
//public:
//	CListBox m_ctrlListDevices;
//	/*afx_msg void OnBnClickedButSelectSource();
//	afx_msg void OnBnClickedButGrabImage();
//	afx_msg void OnTimer(UINT_PTR nIDEvent);*/
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
