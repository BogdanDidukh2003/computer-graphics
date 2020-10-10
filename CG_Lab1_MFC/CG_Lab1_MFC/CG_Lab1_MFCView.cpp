
// CG_Lab1_MFCView.cpp : implementation of the CCGLab1MFCView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CG_Lab1_MFC.h"
#endif

#include "CG_Lab1_MFCDoc.h"
#include "CG_Lab1_MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void drawDiode(CDC* pDC, const int& x, const int& y, const int& width, const int& lineWidth = 50);

// CCGLab1MFCView

IMPLEMENT_DYNCREATE(CCGLab1MFCView, CView)

BEGIN_MESSAGE_MAP(CCGLab1MFCView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCGLab1MFCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CCGLab1MFCView construction/destruction

CCGLab1MFCView::CCGLab1MFCView() noexcept
{
	// TODO: add construction code here

}

CCGLab1MFCView::~CCGLab1MFCView()
{
}

BOOL CCGLab1MFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCGLab1MFCView drawing

void CCGLab1MFCView::OnDraw(CDC* pDC)  // Device Context
{
	CCGLab1MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	drawDiode(pDC, 100, 100, 50);
}

void drawDiode(CDC* pDC, const int& x, const int& y, const int& width, const int& lineWidth) {
	pDC->MoveTo(x, y + width / 2);
	pDC->LineTo(x + lineWidth, y + width / 2);

	POINT triangleVertices[] = { {x + lineWidth, y}, {x + lineWidth, y + width}, {x + lineWidth + width, y + width / 2} };
	pDC->Polygon(triangleVertices, sizeof(triangleVertices) / sizeof(triangleVertices[0]));
	pDC->MoveTo(x + lineWidth + width, y);
	pDC->LineTo(x + lineWidth + width, y + width);

	pDC->MoveTo(x + lineWidth + width, y + width / 2);
	pDC->LineTo(x + 2 * lineWidth + width, y + width / 2);

	pDC->TextOutW(x, y + width / 2 + 10, _T("A"));
	pDC->TextOutW(x + 2 * lineWidth + width - 10, y + width / 2 + 10, _T("K"));
}


// CCGLab1MFCView printing


void CCGLab1MFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCGLab1MFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCGLab1MFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCGLab1MFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CCGLab1MFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCGLab1MFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCGLab1MFCView diagnostics

#ifdef _DEBUG
void CCGLab1MFCView::AssertValid() const
{
	CView::AssertValid();
}

void CCGLab1MFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCGLab1MFCDoc* CCGLab1MFCView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGLab1MFCDoc)));
	return (CCGLab1MFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CCGLab1MFCView message handlers
