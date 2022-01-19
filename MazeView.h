
// MazeView.h : interface of the CMazeView class
//

#pragma once
#include<mmsystem.h>
#include<mmstream.h>

class CMazeView : public CView
{
protected: // create from serialization only
	CMazeView() noexcept;
	DECLARE_DYNCREATE(CMazeView)

// Attributes
public:
	CMazeDoc* GetDocument() const;

	void ResizeWindow();

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMazeView();
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
public:
	virtual void OnInitialUpdate();
	void draw();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // debug version in MazeView.cpp
inline CMazeDoc* CMazeView::GetDocument() const
   { return reinterpret_cast<CMazeDoc*>(m_pDocument); }
#endif

