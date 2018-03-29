
#pragma once

// CWebcamDirectShowDlg
class CWebcamDirectShowDlg : public CDialog
{

public:
	CWebcamDirectShowDlg(CWnd* pParent = NULL);	


	enum { IDD = IDD_WEBCAM_DIRECTSHOW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	

// Implementation
public:
void CopyImageFromWindow();

protected:
HWND hMyWindow;


protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ctrlListDevices;
	afx_msg void OnBnClickedButSelectSource();
	afx_msg void OnBnClickedButGrabImage();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
