
// Pavlovich_1View.cpp : реализация класса CPavlovich_1View
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Pavlovich_1.h"
#endif

#include "Pavlovich_1Doc.h"
#include "Pavlovich_1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPavlovich_1View

IMPLEMENT_DYNCREATE(CPavlovich_1View, CView)

BEGIN_MESSAGE_MAP(CPavlovich_1View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// создание/уничтожение CPavlovich_1View

CPavlovich_1View::CPavlovich_1View()
{
	// TODO: добавьте код создания
	m_Dragging = 0;
	m_HCross = AfxGetApp()->LoadStandardCursor(IDC_CROSS);

}

CPavlovich_1View::~CPavlovich_1View()
{
}

BOOL CPavlovich_1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs
	m_ClassName = AfxRegisterWndClass(
		CS_HREDRAW | CS_VREDRAW, // стили окна
		0,					  // без указателя;
		(HBRUSH)::GetStockObject(WHITE_BRUSH),
		// задать чисто белый фон;
		0);					  //без значка
	cs.lpszClass = m_ClassName;

	return CView::PreCreateWindow(cs);
}

// рисование CPavlovich_1View

void CPavlovich_1View::OnDraw(CDC* pDC)
{
	CPavlovich_1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	int Index = pDoc->GetNumLines();
	while (Index--)
		pDoc->GetLine(Index)->Draw(pDC);

	// TODO: добавьте здесь код отрисовки для собственных данных
}

void CPavlovich_1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPavlovich_1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// диагностика CPavlovich_1View

#ifdef _DEBUG
void CPavlovich_1View::AssertValid() const
{
	CView::AssertValid();
}

void CPavlovich_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPavlovich_1Doc* CPavlovich_1View::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPavlovich_1Doc)));
	return (CPavlovich_1Doc*)m_pDocument;
}
#endif //_DEBUG


// обработчики сообщений CPavlovich_1View


void CPavlovich_1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	m_PointOld = point;
	m_PointOrigin = point;

	SetCapture();
	m_Dragging = 1;

	RECT Rect;
	GetClientRect(&Rect);
	ClientToScreen(&Rect);
	::ClipCursor(&Rect);
	CView::OnLButtonDown(nFlags, point);
}


void CPavlovich_1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	::SetCursor(m_HCross);

	if (m_Dragging)

	{


		CClientDC ClientDC(this);
		ClientDC.SetROP2(R2_NOT);
		ClientDC.MoveTo(m_PointOrigin);
		CBrush* pOldBrush = (CBrush*)ClientDC.SelectStockObject(NULL_BRUSH);

		ClientDC.MoveTo(m_PointOrigin);
		ClientDC.Ellipse(m_PointOrigin.x, m_PointOrigin.y, m_PointOld.x, m_PointOld.y);
		ClientDC.MoveTo(m_PointOrigin);

		if ((m_PointOrigin.y - point.y) > 0) {
			ClientDC.Ellipse(m_PointOrigin.x, m_PointOrigin.y, point.x, ((m_PointOrigin.y - (fabs((double)m_PointOrigin.x - point.x)))));
			m_PointOld.x = point.x;
			m_PointOld.y = ((m_PointOrigin.y - (fabs((double)m_PointOrigin.x - point.x))));
		}
		else
		{
			ClientDC.Ellipse(m_PointOrigin.x, m_PointOrigin.y, point.x, ((m_PointOrigin.y + (fabs((double)m_PointOrigin.x - point.x)))));
			m_PointOld.x = point.x;
			m_PointOld.y = ((m_PointOrigin.y + (fabs((double)m_PointOrigin.x - point.x))));
		}
	}

	CView::OnMouseMove(nFlags, point);
}


void CPavlovich_1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	

	if (m_Dragging)

	{
		m_Dragging = 0;
		::ReleaseCapture();
		::ClipCursor(NULL);
		CClientDC ClientDC(this);


		CBrush* pOldBrush = (CBrush*)ClientDC.SelectStockObject(NULL_BRUSH);


		ClientDC.MoveTo(m_PointOrigin);
		ClientDC.Ellipse(m_PointOrigin.x, m_PointOrigin.y, m_PointOld.x, m_PointOld.y);
		ClientDC.SetROP2(R2_COPYPEN);
		ClientDC.MoveTo(m_PointOrigin);
		CPavlovich_1Doc* pDoc = GetDocument();
		pDoc->AddLine(m_PointOrigin.x, m_PointOrigin.y, point.x, point.y);
	}
	CView::OnLButtonUp(nFlags, point);

}
