
// DentalTechnologistAssistView.h : CDentalTechnologistAssistView Ŭ������ �������̽�
//

#pragma once


class CDentalTechnologistAssistView : public CView
{
protected: // serialization������ ��������ϴ�.
	CDentalTechnologistAssistView();
	DECLARE_DYNCREATE(CDentalTechnologistAssistView)

// Ư���Դϴ�.
public:
	CDentalTechnologistAssistDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CDentalTechnologistAssistView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // DentalTechnologistAssistView.cpp�� ����� ����
inline CDentalTechnologistAssistDoc* CDentalTechnologistAssistView::GetDocument() const
   { return reinterpret_cast<CDentalTechnologistAssistDoc*>(m_pDocument); }
#endif

