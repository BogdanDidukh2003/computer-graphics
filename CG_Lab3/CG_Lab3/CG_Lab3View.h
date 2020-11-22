
// CG_Lab3View.h : interface of the CCGLab3View class
//

#pragma once


class CCGLab3View : public CView
{
protected: // create from serialization only
	CCGLab3View() noexcept;
	DECLARE_DYNCREATE(CCGLab3View)

// Attributes
public:
	CCGLab3Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CCGLab3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CG_Lab3View.cpp
inline CCGLab3Doc* CCGLab3View::GetDocument() const
   { return reinterpret_cast<CCGLab3Doc*>(m_pDocument); }
#endif

