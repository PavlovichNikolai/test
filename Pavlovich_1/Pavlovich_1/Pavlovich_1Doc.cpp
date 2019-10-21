
// Pavlovich_1Doc.cpp : ���������� ������ CPavlovich_1Doc
//

#include "stdafx.h"
// SHARED_HANDLERS ����� ���������� � ������������ �������� ��������� ���������� ������� ATL, �������
// � ������; ��������� ��������� ������������ ��� ��������� � ������ �������.
#ifndef SHARED_HANDLERS
#include "Pavlovich_1.h"
#endif

#include "Pavlovich_1Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPavlovich_1Doc

IMPLEMENT_DYNCREATE(CPavlovich_1Doc, CDocument)

BEGIN_MESSAGE_MAP(CPavlovich_1Doc, CDocument)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, &CPavlovich_1Doc::OnEditClearAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, &CPavlovich_1Doc::OnUpdateEditClearAll)
	ON_COMMAND(ID_EDIT_UNDO, &CPavlovich_1Doc::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CPavlovich_1Doc::OnUpdateEditUndo)
END_MESSAGE_MAP()


// ��������/����������� CPavlovich_1Doc

CPavlovich_1Doc::CPavlovich_1Doc()
{
	// TODO: �������� ��� ��� ������������ ������ ������������

}

CPavlovich_1Doc::~CPavlovich_1Doc()
{
}

BOOL CPavlovich_1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �������� ��� ��������� �������������
	// (��������� SDI ����� �������� ������������ ���� ��������)

	return TRUE;
}




// ������������ CPavlovich_1Doc

void CPavlovich_1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �������� ��� ����������
		m_LineArray.Serialize(ar);
	}
	else
	{
		// TODO: �������� ��� ��������
		m_LineArray.Serialize(ar);
	}
}

#ifdef SHARED_HANDLERS

// ��������� ��� �������
void CPavlovich_1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �������� ���� ��� ��� ����������� ������ ���������
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ��������� ������������ ������
void CPavlovich_1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������� ���������� ������ �� ������ ���������. 
	// ����� ����������� ������ ����������� ������ � ������� ";"

	// ��������:  strSearchContent = _T("�����;�������������;����;������ ole;");
	SetSearchContent(strSearchContent);
}

void CPavlovich_1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// ����������� CPavlovich_1Doc

#ifdef _DEBUG
void CPavlovich_1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPavlovich_1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// ������� CPavlovich_1Doc
IMPLEMENT_SERIAL(CLine, CObject, 1)
void CLine::Draw(CDC *PDC)
{
	if ((m_Y1 - m_Y2) > 0) {
		PDC->Ellipse(m_X1, m_Y1, m_X2, ((m_Y1 - (fabs((double)m_X1 - m_X2)))));
		
	}
	else
	{
		PDC->Ellipse(m_X1, m_Y1, m_X2, ((m_Y1 + (fabs((double)m_X1 - m_X2)))));
		
	}
	
	
}
void CLine::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
		ar << m_X1 << m_Y1 << m_X2 << m_Y2;
	else
		ar >> m_X1 >> m_Y1 >> m_X2 >> m_Y2;
}

void CPavlovich_1Doc::AddLine(int X1, int Y1, int X2, int Y2)
{
	CLine *pLine = new CLine(X1, Y1, X2, Y2);
	m_LineArray.Add(pLine);
	SetModifiedFlag();
}
CLine* CPavlovich_1Doc::GetLine(int Index)
{
	if (Index<0 || Index>m_LineArray.GetUpperBound())
		return 0;
	return m_LineArray.GetAt(Index);
}

int CPavlovich_1Doc::GetNumLines()
{
	return (int)m_LineArray.GetSize();
}


void CPavlovich_1Doc::DeleteContents()
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
	int Index = (int)m_LineArray.GetSize();
	while (Index--)
		delete m_LineArray.GetAt(Index);
	m_LineArray.RemoveAll();

	CDocument::DeleteContents();
}


void CPavlovich_1Doc::OnEditClearAll()
{
	// TODO: �������� ���� ��� ����������� ������
	DeleteContents();
	UpdateAllViews(0);
	SetModifiedFlag();
}


void CPavlovich_1Doc::OnUpdateEditClearAll(CCmdUI *pCmdUI)
{
	// TODO: �������� ���� ��� ����������� �� ���������� ������
	pCmdUI->Enable((int)m_LineArray.GetSize());
}


void CPavlovich_1Doc::OnEditUndo()
{
	// TODO: �������� ���� ��� ����������� ������
	int Index = (int)m_LineArray.GetUpperBound();
	if (Index>-1)
	{
		delete m_LineArray.GetAt(Index);
		m_LineArray.RemoveAt(Index);
	}
	UpdateAllViews(0);
	SetModifiedFlag();
}


void CPavlovich_1Doc::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	// TODO: �������� ���� ��� ����������� �� ���������� ������
	pCmdUI->Enable((int)m_LineArray.GetSize());
}
