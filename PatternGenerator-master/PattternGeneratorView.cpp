// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// PattternGeneratorView.cpp : implementation of the CPattternGeneratorView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PattternGenerator.h"
#endif

#include "PattternGeneratorDoc.h"
#include "PattternGeneratorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPattternGeneratorView

IMPLEMENT_DYNCREATE(CPattternGeneratorView, CView)

BEGIN_MESSAGE_MAP(CPattternGeneratorView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPattternGeneratorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_START, &CPattternGeneratorView::OnButtonStart)
	ON_COMMAND(ID_RESUME, &CPattternGeneratorView::OnResume)
	ON_COMMAND(ID_BUTTON_SUSPEND, &CPattternGeneratorView::OnButtonSuspend)
END_MESSAGE_MAP()

// CPattternGeneratorView construction/destruction

CPattternGeneratorView::CPattternGeneratorView() noexcept
{
	// TODO: add construction code here
	m_pCurrentThread = NULL;

	x = 400;
	y = 200;

	x1 = 300 + 150 * cos(3);
	y1 = 200 + 150 * sin(3);

	x2 = 200 + 200 * cos(6);
	y2 = 200 + 200 * sin(6);

}

CPattternGeneratorView::~CPattternGeneratorView()
{
}

BOOL CPattternGeneratorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPattternGeneratorView drawing

void CPattternGeneratorView::OnDraw(CDC* pDC)
{
	CPattternGeneratorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	pDC->Ellipse(500, 400, 100, 0); //earth
	
	pDC->Ellipse(450, 350, 150, 50); // venus

	pDC->Ellipse(400, 300, 200, 100); // mercury 

	CBrush brushyellow(RGB(255, 102, 0));
	CBrush* pO1dBrush = pDC-> SelectObject(&brushyellow);
	pDC->Ellipse(330, 230, 270, 170);      // Sun
	pDC->SelectObject(pO1dBrush);

	CBrush brushBlack1(RGB(0, 0, 0));
	CBrush* pO2dBrush = pDC->SelectObject(&brushBlack1);//mercury size
	pDC->Ellipse(x + 10, y + 10, x - 10, y - 10);
	pDC->SelectObject(pO2dBrush);

	CBrush brushBlack2(RGB(0, 0, 0));
	CBrush* pO3dBrush = pDC->SelectObject(&brushBlack2);//venus
	pDC->Ellipse(x1 + 10, y1 + 10, x1 - 10, y1 - 10);
	pDC->SelectObject(pO3dBrush);

	CBrush brushBlack3(RGB(0, 0, 0));
	CBrush* pO4dBrush = pDC->SelectObject(&brushBlack3);//earth
	pDC->Ellipse(x2 + 10, y2 + 10, x2 - 10, y2 - 10);
	pDC->SelectObject(pO4dBrush);

	
	// TODO: add draw code for native data here
}


// CPattternGeneratorView printing


void CPattternGeneratorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPattternGeneratorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPattternGeneratorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPattternGeneratorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPattternGeneratorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPattternGeneratorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPattternGeneratorView diagnostics

#ifdef _DEBUG
void CPattternGeneratorView::AssertValid() const
{
	CView::AssertValid();
}

void CPattternGeneratorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPattternGeneratorDoc* CPattternGeneratorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPattternGeneratorDoc)));
	return (CPattternGeneratorDoc*)m_pDocument;
}
#endif //_DEBUG


// CPattternGeneratorView message handlers


void CPattternGeneratorView::OnButtonStart()
{
	// TODO: Add your command handler code here
	m_pCurrentThread=AfxBeginThread(CPattternGeneratorView::StartThread,this);
}

void CPattternGeneratorView::OnButtonSuspend()
{
	m_pCurrentThread->SuspendThread();
}

void CPattternGeneratorView::OnResume()
{
	m_pCurrentThread->ResumeThread();
}





UINT CPattternGeneratorView::StartThread(LPVOID Param)
{
	CPattternGeneratorView* pView = (CPattternGeneratorView*)Param;
	CPoint MyPoint(0, 0);
	int j = 0;
	while (1)
	{

		j = j + 6;
		pView->x =300 + 100 * cos(j); //l
		pView->y = 200 + 100 * sin(j); //b

    	pView->x1 = 300 + 150 * cos(j + 3);
		pView->y1 = 200 + 150 * sin(j + 3);

		pView->x2 = 300 + 200 * cos(j + 10);
		pView->y2 = 200 + 200 * sin(j + 10);

		
		pView->Invalidate();
		Sleep(80);
	}
	return 0;
}
 