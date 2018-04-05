
// DentalTechnologistAssistView.cpp : CDentalTechnologistAssistView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "DentalTechnologistAssist.h"
#endif

#include "DentalTechnologistAssistDoc.h"
#include "DentalTechnologistAssistView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDentalTechnologistAssistView

IMPLEMENT_DYNCREATE(CDentalTechnologistAssistView, CView)

BEGIN_MESSAGE_MAP(CDentalTechnologistAssistView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDentalTechnologistAssistView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CDentalTechnologistAssistView ����/�Ҹ�

CDentalTechnologistAssistView::CDentalTechnologistAssistView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CDentalTechnologistAssistView::~CDentalTechnologistAssistView()
{
}

BOOL CDentalTechnologistAssistView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CDentalTechnologistAssistView �׸���

void CDentalTechnologistAssistView::OnDraw(CDC* /*pDC*/)
{
	CDentalTechnologistAssistDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CDentalTechnologistAssistView �μ�


void CDentalTechnologistAssistView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDentalTechnologistAssistView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CDentalTechnologistAssistView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CDentalTechnologistAssistView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CDentalTechnologistAssistView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDentalTechnologistAssistView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDentalTechnologistAssistView ����

#ifdef _DEBUG
void CDentalTechnologistAssistView::AssertValid() const
{
	CView::AssertValid();
}

void CDentalTechnologistAssistView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDentalTechnologistAssistDoc* CDentalTechnologistAssistView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDentalTechnologistAssistDoc)));
	return (CDentalTechnologistAssistDoc*)m_pDocument;
}
#endif //_DEBUG


// CDentalTechnologistAssistView �޽��� ó����
