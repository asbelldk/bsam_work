
// DentalTechnologistAssistView.h : CDentalTechnologistAssistView 클래스의 인터페이스
//

#pragma once


class CDentalTechnologistAssistView : public CView
{
protected: // serialization에서만 만들어집니다.
	CDentalTechnologistAssistView();
	DECLARE_DYNCREATE(CDentalTechnologistAssistView)

// 특성입니다.
public:
	CDentalTechnologistAssistDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//afx_msg void OnPaint();

// 구현입니다.
public:
	virtual ~CDentalTechnologistAssistView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // DentalTechnologistAssistView.cpp의 디버그 버전
inline CDentalTechnologistAssistDoc* CDentalTechnologistAssistView::GetDocument() const
   { return reinterpret_cast<CDentalTechnologistAssistDoc*>(m_pDocument); }
#endif

