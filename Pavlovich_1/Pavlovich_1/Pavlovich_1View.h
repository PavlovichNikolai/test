
// Pavlovich_1View.h : ��������� ������ CPavlovich_1View
//

#pragma once


class CPavlovich_1View : public CView
{
protected: // ������� ������ �� ������������
	CPavlovich_1View();
	DECLARE_DYNCREATE(CPavlovich_1View)
protected:
	CString m_ClassName;
	int m_Dragging;
	HCURSOR m_HCross;
	CPoint m_PointOld;
	CPoint m_PointOrigin;

// ��������
public:
	CPavlovich_1Doc* GetDocument() const;

// ��������
public:

// ���������������
public:
	virtual void OnDraw(CDC* pDC);  // �������������� ��� ��������� ����� �������������
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ����������
public:
	virtual ~CPavlovich_1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ��������� ������� ����� ���������
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // ���������� ������ � Pavlovich_1View.cpp
inline CPavlovich_1Doc* CPavlovich_1View::GetDocument() const
   { return reinterpret_cast<CPavlovich_1Doc*>(m_pDocument); }
#endif

