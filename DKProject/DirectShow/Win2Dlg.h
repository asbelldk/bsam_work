#pragma once



class CWin2Dlg : public CDialog
{
	DECLARE_DYNAMIC(CWin2Dlg)

public:
	CWin2Dlg(CWnd* pParent = NULL);   
	virtual ~CWin2Dlg();

//
	enum { IDD = IDD_WIN2 };

HRESULT BitmapSaveToFile(char *pFileName, BITMAPINFO *pBMI, size_t cbBMI, BYTE *pData, size_t cbData);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBut180();
	afx_msg void OnBnClickedButSaveBmp();
	afx_msg void OnBnClickedButColorToGrey();
	afx_msg void OnBnClickedButBlackWhite();
	afx_msg void OnBnClickedButTakePicture();
	afx_msg void OnBnClickedCheckGray();


	BOOL b_checkgreyed;
	BOOL b_checkleftright;


	afx_msg void OnBnClickedCheckFilter();
	
	BOOL b_check_filter;
	BOOL b_check_filter2;
	int m_iCx11,m_iCx12,m_iCx13;
	int	m_iCx21,m_iCx22,m_iCx23;
	int m_iCx31,m_iCx32,m_iCx33;
	int m_iDiv1;
	int m_iDx11,m_iDx12,m_iDx13;
	int	m_iDx21,m_iDx22,m_iDx23;
	int m_iDx31,m_iDx32,m_iDx33;
	int m_iDiv2;
	afx_msg void OnBnClickedButMedian1();
	afx_msg void OnBnClickedButGauss1();
	afx_msg void OnBnClickedButHh1();

	void Sharpening(void);
	afx_msg void OnBnClickedCheckFilter2();
	afx_msg void OnBnClickedButHp1();
	afx_msg void OnBnClickedButHp2();
	afx_msg void OnBnClickedButHp3();
	void CalcNew(void);
	afx_msg void OnBnClickedCheckLeftRight();
	afx_msg void OnBnClickedButHistogram();
	void CopyToOutArray(void);
	afx_msg void OnBnClickedButLeftRight();
	afx_msg void OnBnClickedButCalcFilter1();
	void SetInputOutput(void);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedButGauss2();
	afx_msg void OnBnClickedButAverage();
};
