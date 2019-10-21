
// Pavlovich_1Doc.h : интерфейс класса CPavlovich_1Doc
//


#pragma once
class CLine : public CObject
{
protected:
	int m_X1, m_Y1, m_X2, m_Y2;
	CLine() {}
	DECLARE_SERIAL(CLine)
public:
	CLine(int X1, int Y1, int X2, int Y2)
	{
		m_X1 = X1; m_Y1 = Y1; m_X2 = X2; m_Y2 = Y2;
	}
	void Draw(CDC *PDC);
	virtual void Serialize(CArchive& ar);
};


class CPavlovich_1Doc : public CDocument
{
protected: // создать только из сериализации
	CPavlovich_1Doc();
	DECLARE_DYNCREATE(CPavlovich_1Doc)
protected:
	CTypedPtrArray<CObArray, CLine*> m_LineArray;
public:
	void AddLine(int X1, int Y1, int X2, int Y2);
	CLine *GetLine(int Index);
	int GetNumLines();

// Атрибуты
public:

// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CPavlovich_1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual void DeleteContents();
	afx_msg void OnEditClearAll();
	afx_msg void OnUpdateEditClearAll(CCmdUI *pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
};
