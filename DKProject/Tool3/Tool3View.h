
// Tool3View.h : CTool3View Ŭ������ �������̽�
//

#pragma once


class CTool3View : public CView
{
protected: // serialization������ ��������ϴ�.
	CTool3View();
	DECLARE_DYNCREATE(CTool3View)

// Ư���Դϴ�.
public:
	CTool3Doc* GetDocument() const;

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
	virtual ~CTool3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Tool3View.cpp�� ����� ����
inline CTool3Doc* CTool3View::GetDocument() const
   { return reinterpret_cast<CTool3Doc*>(m_pDocument); }
#endif

