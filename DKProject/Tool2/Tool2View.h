
// Tool2View.h : CTool2View Ŭ������ �������̽�
//

#pragma once


class CTool2View : public CView
{
protected: // serialization������ ��������ϴ�.
	CTool2View();
	DECLARE_DYNCREATE(CTool2View)

// Ư���Դϴ�.
public:
	CTool2Doc* GetDocument() const;

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
	virtual ~CTool2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Tool2View.cpp�� ����� ����
inline CTool2Doc* CTool2View::GetDocument() const
   { return reinterpret_cast<CTool2Doc*>(m_pDocument); }
#endif

