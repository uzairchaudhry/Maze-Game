
// MazeView.cpp : implementation of the CMazeView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Maze.h"
#endif

#include "MazeDoc.h"
#include "MazeView.h"
#include "MazeTraversal.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMazeView

IMPLEMENT_DYNCREATE(CMazeView, CView)

BEGIN_MESSAGE_MAP(CMazeView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMazeView construction/destruction

CMazeView::CMazeView() noexcept
{
	// TODO: add construction code here

}

CMazeView::~CMazeView()
{
}

BOOL CMazeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMazeView drawing

void CMazeView::OnDraw(CDC* pDC)
{
	CMazeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
//	PlaySound(_T("images\\sound1.wav"), NULL, SND_FILENAME | SND_ASYNC);
	
	/*CImage* cimage = new CImage();
	cimage->Load(L"images\\brickwall1.png");//images folder is placed in working directory
	cimage->Draw(pDC->m_hDC, 0,0, 880, 600);
	cimage->Destroy();
	Sleep(1000);*/
	draw();
/*	CImage* cimage = new CImage();
	cimage->Load(L"images\\Right.png");//images folder is placed in working directory
	cimage->Draw(0,0,120, 170, 170);
	//cimage->Destroy();*/
//	SetTimer(1, 100, NULL);
	// TODO: add draw code for native data here
}

void CMazeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMazeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMazeView diagnostics

#ifdef _DEBUG
void CMazeView::AssertValid() const
{
	CView::AssertValid();
}

void CMazeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMazeDoc* CMazeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMazeDoc)));
	return (CMazeDoc*)m_pDocument;
}
#endif //_DEBUG


// CMazeView message handlers


void CMazeView::ResizeWindow()
{

	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);
	//  Calculate the difference
	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();
	//  Change the window size as 100x100
	rcWindow.right = rcWindow.left + 880 + nWidthDiff;
	rcWindow.bottom = rcWindow.top + 600 + nHeightDiff;
	//  The MoveWindow function resizes the frame window
	GetParentFrame()->MoveWindow(&rcWindow);
}

void CMazeView::OnInitialUpdate()
{
	ResizeWindow();
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
}
void CMazeView::draw()
{
	CMazeDoc* pDoc = GetDocument();
	CDC* pDC = GetDC();
	int x = pDoc->ptr.getCellWidthPx();
	int y=pDoc->ptr.getCellHeightPx();
	int b = 0;
	for (int i = 0; i < (pDoc->ptr.getrSize()); i++)
	{
		int a = 0;
		for (int j = 0; j < (pDoc->ptr.getcSize()); j++)
		{	
			if (pDoc->ptr.getCellValueAt(i, j) == '#')
			{
					//pDC->FillSolidRect(a, b, 40, 40, RGB(250, 1, 0));
					CImage* cimage = new CImage();
					cimage->Load(L"images\\wall3.png");//images folder is placed in working directory
					cimage->Draw(pDC->m_hDC, a, b, 40,40);
					cimage->Destroy();
			}
			else if (i == pDoc->ptr.getStartRow() && j == pDoc->ptr.getStartCol())
			{
				CImage* cimage = new CImage();
				cimage->Load(L"images\\Right.png");//images folder is placed in working directory
				cimage->Draw(pDC->m_hDC, a, b, 40, 40);
				cimage->Destroy();
			}
			else if (pDoc->ptr.getCellValueAt(i, j) == '.')
			{
				pDC->FillSolidRect(a, b, 40, 40, RGB(1, 256, 0));
			}
			a += 40;
		}
		b += 40;
	}
}


void CMazeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
	CMazeDoc* pDoc = GetDocument();
	CDC* pDC = GetDC();
	// TODO: Add your message handler code here and/or call default
	if (nChar == VK_UP)
	{
		pDoc->ptr.moveUp(pDC);
	}
	if (nChar == VK_LEFT)
	{
		pDoc->ptr.moveLeft(pDC);
	}
	if (nChar == VK_RIGHT)
	{
		pDoc->ptr.moveRight(pDC);
	}
	if (nChar == VK_DOWN)
	{
		pDoc->ptr.moveDown(pDC);
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMazeView::OnTimer(UINT_PTR nIDEvent)
{
	CMazeDoc* pDoc = GetDocument();
	CDC* pDC = GetDC();
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent==1)
	pDoc->ptr.moveToNextCell(pDC);
	CView::OnTimer(nIDEvent);
}