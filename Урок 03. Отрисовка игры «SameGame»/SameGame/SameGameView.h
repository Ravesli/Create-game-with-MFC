
// SameGameView.h : interface of the CSameGameView class
//

#pragma once


class CSameGameView : public CView
{
protected: // create from serialization only
	CSameGameView() noexcept;
	DECLARE_DYNCREATE(CSameGameView)

// Attributes
public:
	CSameGameDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	void ResizeWindow();

	virtual ~CSameGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // debug version in SameGameView.cpp
inline CSameGameDoc* CSameGameView::GetDocument() const
   { return reinterpret_cast<CSameGameDoc*>(m_pDocument); }
#endif

