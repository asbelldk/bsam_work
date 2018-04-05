
// DentalTechnologistAssistView.cpp : CDentalTechnologistAssistView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDentalTechnologistAssistView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CDentalTechnologistAssistView 생성/소멸

CDentalTechnologistAssistView::CDentalTechnologistAssistView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CDentalTechnologistAssistView::~CDentalTechnologistAssistView()
{
}

BOOL CDentalTechnologistAssistView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CDentalTechnologistAssistView 그리기

void CDentalTechnologistAssistView::OnDraw(CDC* /*pDC*/)
{
	CDentalTechnologistAssistDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CDentalTechnologistAssistView 인쇄


void CDentalTechnologistAssistView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDentalTechnologistAssistView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CDentalTechnologistAssistView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CDentalTechnologistAssistView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
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


// CDentalTechnologistAssistView 진단

#ifdef _DEBUG
void CDentalTechnologistAssistView::AssertValid() const
{
	CView::AssertValid();
}

void CDentalTechnologistAssistView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDentalTechnologistAssistDoc* CDentalTechnologistAssistView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDentalTechnologistAssistDoc)));
	return (CDentalTechnologistAssistDoc*)m_pDocument;
}
#endif //_DEBUG


// CDentalTechnologistAssistView 메시지 처리기
