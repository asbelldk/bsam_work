
// Tool2View.cpp : CTool2View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Tool2.h"
#endif

#include "Tool2Doc.h"
#include "Tool2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTool2View

IMPLEMENT_DYNCREATE(CTool2View, CView)

BEGIN_MESSAGE_MAP(CTool2View, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CTool2View ����/�Ҹ�

CTool2View::CTool2View()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CTool2View::~CTool2View()
{
}

BOOL CTool2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CTool2View �׸���

void CTool2View::OnDraw(CDC* /*pDC*/)
{
	CTool2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CTool2View �μ�

BOOL CTool2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CTool2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CTool2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CTool2View ����

#ifdef _DEBUG
void CTool2View::AssertValid() const
{
	CView::AssertValid();
}

void CTool2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTool2Doc* CTool2View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTool2Doc)));
	return (CTool2Doc*)m_pDocument;
}
#endif //_DEBUG


// CTool2View �޽��� ó����
