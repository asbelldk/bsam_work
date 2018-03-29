
// Tool3View.cpp : CTool3View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Tool3.h"
#endif

#include "Tool3Doc.h"
#include "Tool3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTool3View

IMPLEMENT_DYNCREATE(CTool3View, CView)

BEGIN_MESSAGE_MAP(CTool3View, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CTool3View ����/�Ҹ�

CTool3View::CTool3View()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CTool3View::~CTool3View()
{
}

BOOL CTool3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CTool3View �׸���

void CTool3View::OnDraw(CDC* /*pDC*/)
{
	CTool3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CTool3View �μ�

BOOL CTool3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CTool3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CTool3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CTool3View ����

#ifdef _DEBUG
void CTool3View::AssertValid() const
{
	CView::AssertValid();
}

void CTool3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTool3Doc* CTool3View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTool3Doc)));
	return (CTool3Doc*)m_pDocument;
}
#endif //_DEBUG


// CTool3View �޽��� ó����
