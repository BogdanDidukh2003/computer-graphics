
// CG_Lab3View.cpp : implementation of the CCGLab3View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CG_Lab3.h"
#endif

#include "CG_Lab3Doc.h"
#include "CG_Lab3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void DrawPixel(CDC* pDC, int x, int y, int size, int baseColor) {
    pDC->SetPixel(x, y, baseColor);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            pDC->SetPixel(x + i, y + j, baseColor);
        }
    }
}

void DrawWuLine(CDC* pDC, short X0, short Y0, short X1, short Y1,
    short BaseColor, short NumLevels, unsigned short IntensityBits, int size)
{
    unsigned short IntensityShift, ErrorAdj, ErrorAcc;
    unsigned short ErrorAccTemp, Weighting, WeightingComplementMask;
    short DeltaX, DeltaY, Temp, XDir;

    /* Make sure the line runs top to bottom */
    if (Y0 > Y1) {
        Temp = Y0; Y0 = Y1; Y1 = Temp;
        Temp = X0; X0 = X1; X1 = Temp;
    }
    /* Draw the initial pixel, which is always exactly intersected by
       the line and so needs no weighting */
    DrawPixel(pDC, X0, Y0, size, BaseColor);

    if ((DeltaX = X1 - X0) >= 0) {
        XDir = size;
    }
    else {
        XDir = -size;
        DeltaX = -DeltaX; /* make DeltaX positive */
    }
    /* Special-case horizontal, vertical, and diagonal lines, which
       require no weighting because they go right through the center of
       every pixel */
    if ((DeltaY = Y1 - Y0) == 0) {
        /* Horizontal line */
        while ((abs(DeltaX) - size) < 0) {
            DeltaX -= size;
            X0 += XDir;
            DrawPixel(pDC, X0, Y0, size, BaseColor);
        }
        return;
    }
    if (DeltaX == 0) {
        /* Vertical line */
        do {
            DeltaY -= size;
            Y0 += size;
            DrawPixel(pDC, X0, Y0, size, BaseColor);
        } while ((abs(DeltaY) - size) != 0);
        return;
    }
    if (DeltaX == DeltaY) {
        /* Diagonal line */
        do {
            DeltaY -= size;
            X0 += XDir;
            Y0 += size;
            DrawPixel(pDC, X0, Y0, size, BaseColor);
        } while ((abs(DeltaY) - size) != 0);
        return;
    }
    /* Line is not horizontal, diagonal, or vertical */
    ErrorAcc = 0;  /* initialize the line error accumulator to 0 */
    /* # of bits by which to shift ErrorAcc to get intensity level */
    IntensityShift = 16 - IntensityBits;
    /* Mask used to flip all bits in an intensity weighting, producing the
       result (1 - intensity weighting) */
    WeightingComplementMask = NumLevels - 1;
    /* Is this an X-major or Y-major line? */
    if (DeltaY > DeltaX) {
        /* Y-major line; calculate 16-bit fixed-point fractional part of a
           pixel that X advances each time Y advances 1 pixel, truncating the
           result so that we won't overrun the endpoint along the X axis */
        ErrorAdj = ((unsigned long)DeltaX << 16) / (unsigned long)DeltaY;
        /* Draw all pixels other than the first and last */
        while ((abs(DeltaY) - size) > 0) {
            DeltaY -= size;
            ErrorAccTemp = ErrorAcc;   /* remember current accumulated error */
            ErrorAcc += ErrorAdj;      /* calculate error for next pixel */
            if (ErrorAcc <= ErrorAccTemp) {
                /* The error accumulator turned over, so advance the X coord */
                X0 += XDir;
            }
            Y0 += size; /* Y-major, so always advance Y */
            /* The IntensityBits most significant bits of ErrorAcc give us the
               intensity weighting for this pixel, and the complement of the
               weighting for the paired pixel */
            Weighting = ErrorAcc >> IntensityShift;
            DrawPixel(pDC, X0, Y0, size, BaseColor + Weighting);
            DrawPixel(pDC, X0 + XDir, Y0, size,
                BaseColor + (Weighting ^ WeightingComplementMask));
        }
        /* Draw the final pixel, which is
           always exactly intersected by the line
           and so needs no weighting */
        DrawPixel(pDC, X1, Y1, size, BaseColor);
        return;
    }
    /* It's an X-major line; calculate 16-bit fixed-point fractional part of a
       pixel that Y advances each time X advances 1 pixel, truncating the
       result to avoid overrunning the endpoint along the X axis */
    ErrorAdj = ((unsigned long)DeltaY << 16) / (unsigned long)DeltaX;
    /* Draw all pixels other than the first and last */
    while ((abs(DeltaX) - size) > 0) {
        DeltaX -= size;
        ErrorAccTemp = ErrorAcc;   /* remember current accumulated error */
        ErrorAcc += ErrorAdj;      /* calculate error for next pixel */
        if (ErrorAcc <= ErrorAccTemp) {
            /* The error accumulator turned over, so advance the Y coord */
            Y0 += size;
        }
        X0 += XDir; /* X-major, so always advance X */
        /* The IntensityBits most significant bits of ErrorAcc give us the
           intensity weighting for this pixel, and the complement of the
           weighting for the paired pixel */
        Weighting = ErrorAcc >> IntensityShift;
        DrawPixel(pDC, X0, Y0, size, BaseColor + Weighting);
        DrawPixel(pDC, X0, Y0 + size, size,
            BaseColor + (Weighting ^ WeightingComplementMask));
    }
    /* Draw the final pixel, which is always exactly intersected by the line
       and so needs no weighting */
    DrawPixel(pDC, X1, Y1, size, BaseColor);
}

// CCGLab3View

IMPLEMENT_DYNCREATE(CCGLab3View, CView)

BEGIN_MESSAGE_MAP(CCGLab3View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCGLab3View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CCGLab3View construction/destruction

CCGLab3View::CCGLab3View() noexcept
{
	// TODO: add construction code here

}

CCGLab3View::~CCGLab3View()
{
}

BOOL CCGLab3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCGLab3View drawing

void CCGLab3View::OnDraw(CDC* pDC)
{
	CCGLab3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	GetClientRect(rect);
	CPoint center = rect.CenterPoint();
	int width = 50, lineWidth = 50;

    int size = 10;
    DrawWuLine(pDC, center.x * 0.1, center.y * 1.9, center.x * 1.9, center.y * 0.1, 0, 256, 8, size);
}


// CCGLab3View printing


void CCGLab3View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCGLab3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCGLab3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCGLab3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CCGLab3View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCGLab3View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCGLab3View diagnostics

#ifdef _DEBUG
void CCGLab3View::AssertValid() const
{
	CView::AssertValid();
}

void CCGLab3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCGLab3Doc* CCGLab3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGLab3Doc)));
	return (CCGLab3Doc*)m_pDocument;
}
#endif //_DEBUG


// CCGLab3View message handlers
