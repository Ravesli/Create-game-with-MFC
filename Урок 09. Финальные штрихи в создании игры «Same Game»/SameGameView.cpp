
// SameGameView.cpp: реализация класса CSameGameView
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SameGame.h"
#endif

#include "SameGameDoc.h"
#include "SameGameView.h"
#include "OptionDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSameGameView

IMPLEMENT_DYNCREATE(CSameGameView, CView)

BEGIN_MESSAGE_MAP(CSameGameView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()

	ON_COMMAND(ID_LEVEL_3COLORS, &CSameGameView::OnLevel3colors)
	ON_COMMAND(ID_LEVEL_4COLORS, &CSameGameView::OnLevel4colors)
	ON_COMMAND(ID_LEVEL_5COLORS, &CSameGameView::OnLevel5colors)
	ON_COMMAND(ID_LEVEL_6COLORS, &CSameGameView::OnLevel6colors)
	ON_COMMAND(ID_LEVEL_7COLORS, &CSameGameView::OnLevel7colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_3COLORS,
		&CSameGameView::OnUpdateLevel3colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_4COLORS,
		&CSameGameView::OnUpdateLevel4colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_5COLORS,
		&CSameGameView::OnUpdateLevel5colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_6COLORS,
		&CSameGameView::OnUpdateLevel6colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_7COLORS,
		&CSameGameView::OnUpdateLevel7colors)

	ON_COMMAND(ID_SETUP_BLOCKCOUNT, &CSameGameView::OnSetupBlockcount)
	ON_COMMAND(ID_SETUP_BLOCKSIZE, &CSameGameView::OnSetupBlocksize)
	ON_UPDATE_COMMAND_UI(ID_SETUP_BLOCKCOUNT, &CSameGameView::OnUpdateSetupBlockcount)
	ON_UPDATE_COMMAND_UI(ID_SETUP_BLOCKSIZE, &CSameGameView::OnUpdateSetupBlocksize)
	ON_COMMAND(ID_32771, &CSameGameView::On32771)
	ON_COMMAND(ID_EDIT_UNDO, &CSameGameView::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CSameGameView::OnUpdateEditUndo)
	ON_UPDATE_COMMAND_UI(ID_32771, &CSameGameView::OnUpdate32771)
	
END_MESSAGE_MAP()

// Создание или уничтожение CSameGameView

CSameGameView::CSameGameView() noexcept
{
	// TODO: добавьте код создания

}

CSameGameView::~CSameGameView()
{
}

BOOL CSameGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs


	return CView::PreCreateWindow(cs);
}


// Рисование CSameGameView

void CSameGameView::OnDraw(CDC* pDC) // MFC will comment out the argument name by default; uncomment it
{
	//  Вначале создаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Сохраняем текущее состояние контекста устройства
	int nDCSave = pDC->SaveDC();
	//  Получаем размеры клиентской области
	CRect rcClient;
	GetClientRect(&rcClient);
	COLORREF clr = pDoc->GetBoardSpace(-1, -1);
	//	Сначала отрисовываем фон
	pDC->FillSolidRect(&rcClient, clr);
	//  Создаем кисть для рисования
	CBrush br;
	br.CreateStockObject(HOLLOW_BRUSH);
	CBrush* pbrOld = pDC->SelectObject(&br);
	//	Рисуем блоки
	for (int row = 0; row < pDoc->GetRows(); row++)
	{
		for (int col = 0; col < pDoc->GetColumns(); col++)
		{
			clr = pDoc->GetBoardSpace(row, col);
			//  Вычисляем размер и позицию игрового пространства
			CRect rcBlock;
			rcBlock.top = row * pDoc->GetHeight();
			rcBlock.left = col * pDoc->GetWidth();
			rcBlock.right = rcBlock.left + pDoc->GetWidth();
			rcBlock.bottom = rcBlock.top + pDoc->GetHeight();
			//  Заполняем блок соответствующим цветом
			pDC->FillSolidRect(&rcBlock, clr);
			//  Рисуем контур
			pDC->Rectangle(&rcBlock);
		}
	}
	//  Восстанавливаем контекст устройства
	pDC->RestoreDC(nDCSave);
	br.DeleteObject();
}

// Диагностика CSameGameView

#ifdef _DEBUG
void CSameGameView::AssertValid() const
{
	CView::AssertValid();
}

void CSameGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSameGameDoc* CSameGameView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSameGameDoc)));
	return (CSameGameDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CSameGameView


void CSameGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//  Вначале создаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Получаем индекс строки и столбца элемента, по которому был клик мышкой
	int row = point.y / pDoc->GetHeight();
	int col = point.x / pDoc->GetWidth();
	//  Удаляем блоки из Document
	int count = pDoc->DeleteBlocks(row, col);
	//  Проверяем, было ли удаление блоков
	if (count > 0)
	{
		//  Перерисовываем View
		Invalidate();
		UpdateWindow();
		//  Проверяем, закончилась ли игра
		if (pDoc->IsGameOver())
		{
			//  Получаем количество оставшихся блоков
			int remaining = pDoc->GetRemainingCount();
			CString message;
			message.Format(_T("Нет доступных ходов\nКоличество оставшихся блоков: %d"),
				remaining);
			//  Отображаем пользователю результат игры
			MessageBox(message, _T("Игра Закончена"), MB_OK | MB_ICONINFORMATION);
		}
	}
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CView::OnLButtonDown(nFlags, point);
}


void CSameGameView::OnInitialUpdate()
{
	
	
	CView::OnInitialUpdate();

	//  Resize the window
	ResizeWindow();

	// TODO: добавьте специализированный код или вызов базового класса
}

void CSameGameView::ResizeWindow()
{
	//  Вначале создаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Получаем размеры клиентской области
	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);
	//  Вычисляем разницу
	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();
	//  Изменяем размеры окна на основе полученных данных
	rcWindow.right = rcWindow.left +
		pDoc->GetWidth() * pDoc->GetColumns() + nWidthDiff;
	rcWindow.bottom = rcWindow.top +
		pDoc->GetHeight() * pDoc->GetRows() + nHeightDiff;
	//  Функция MoveWindow изменяет размеры окна
	GetParentFrame()->MoveWindow(&rcWindow);
}


void CSameGameView::OnLevel3colors()
{
	//  Получаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Задаем число цветов
	pDoc->SetNumColors(3);
	//  Перерисовываем View
	Invalidate();
	UpdateWindow();

	// TODO: добавьте свой код обработчика команд
}


void CSameGameView::OnUpdateLevel3colors(CCmdUI *pCmdUI)
{
	//  Указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Проверка установленного уровня сложности
	pCmdUI->SetCheck(pDoc->GetNumColors() == 3);

	// TODO: добавьте свой код обработчика ИП обновления команд
}


void CSameGameView::OnLevel4colors()
{
	//  Получаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Задаем число цветов
	pDoc->SetNumColors(4);
	//  Перерисовываем View
	Invalidate();
	UpdateWindow();

	// TODO: добавьте свой код обработчика команд
}


void CSameGameView::OnUpdateLevel4colors(CCmdUI *pCmdUI)
{
	//  Указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Проверка установленного уровня сложности
	pCmdUI->SetCheck(pDoc->GetNumColors() == 4);
	// TODO: добавьте свой код обработчика ИП обновления команд
}


void CSameGameView::OnLevel5colors()
{
	//  Получаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Задаем число цветов
	pDoc->SetNumColors(5);
	//  Перерисовываем View
	Invalidate();
	UpdateWindow();

	// TODO: добавьте свой код обработчика команд
}


void CSameGameView::OnUpdateLevel5colors(CCmdUI *pCmdUI)
{
	//  Указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Проверка установленного уровня сложности
	pCmdUI->SetCheck(pDoc->GetNumColors() == 5);
	// TODO: добавьте свой код обработчика ИП обновления команд
}


void CSameGameView::OnLevel6colors()
{
	//  Получаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Задаем число цветов
	pDoc->SetNumColors(6);
	//  Перерисовываем View
	Invalidate();
	UpdateWindow();

	// TODO: добавьте свой код обработчика команд
}


void CSameGameView::OnUpdateLevel6colors(CCmdUI *pCmdUI)
{
	//  Указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Проверка установленного уровня сложности
	pCmdUI->SetCheck(pDoc->GetNumColors() == 6);
	// TODO: добавьте свой код обработчика ИП обновления команд
}


void CSameGameView::OnLevel7colors()
{
	//  Получаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Задаем число цветов
	pDoc->SetNumColors(7);
	//  Перерисовываем View
	Invalidate();
	UpdateWindow();

	// TODO: добавьте свой код обработчика команд
}


void CSameGameView::OnUpdateLevel7colors(CCmdUI *pCmdUI)
{
	//  Указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Проверка установленного уровня сложности
	pCmdUI->SetCheck(pDoc->GetNumColors() == 7);
	// TODO: добавьте свой код обработчика ИП обновления команд
}


void CSameGameView::OnSetupBlockcount()
{
	//  Получаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Создаем Диалоговое окно
	COptionDialog dlg(true, this);
	//  Устанавливаем параметры строк и столбцов
	dlg.m_nValue1 = pDoc->GetRows();
	dlg.m_nValue2 = pDoc->GetColumns();
	//  Отображаем полученное окно
	if (dlg.DoModal() == IDOK)
	{
		//  Удаляем прошлую доску
		pDoc->DeleteBoard();
		//  Устанавливаем значения, введённый пользователем
		pDoc->SetRows(dlg.m_nValue1);
		pDoc->SetColumns(dlg.m_nValue2);
		//  Обновляем доску
		pDoc->SetupBoard();
		//  Изменяем размеры View
		ResizeWindow();
	}
	// TODO: добавьте свой код обработчика команд
}

void CSameGameView::OnSetupBlocksize()
{
	//  Указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Создаем диалоговое окно
	COptionDialog dlg(false, this);
	//  Устанавливаем параметры «Ширины/Высоты»
	dlg.m_nValue1 = pDoc->GetWidth();
	dlg.m_nValue2 = pDoc->GetHeight();
	//  Отображаем окно
	if (dlg.DoModal() == IDOK)
	{
		//  Удаляем доску
		pDoc->DeleteBoard();
		//   Считываем введенные пользователем параметры
		pDoc->SetWidth(dlg.m_nValue1);
		pDoc->SetHeight(dlg.m_nValue2);
		//  Обновляем доску
		pDoc->SetupBoard();
		//  Изменяем размеры View
		ResizeWindow();
	}
	
}




void CSameGameView::OnUpdateSetupBlockcount(CCmdUI *pCmdUI)
{
	// TODO: добавьте свой код обработчика ИП обновления команд
}


void CSameGameView::OnUpdateSetupBlocksize(CCmdUI *pCmdUI)
{
	// TODO: добавьте свой код обработчика ИП обновления команд
}


void CSameGameView::OnEditUndo()
{
	//  Получаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->UndoLast();
	//  Перерисовываем View
	Invalidate();
	UpdateWindow();
}

void CSameGameView::On32771()
{
	//  Получаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->RedoLast();
	//  Перерисовываем View
	Invalidate();
	UpdateWindow();
}

void CSameGameView::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	//  First get a pointer to the document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Enable option if it is available
	pCmdUI->Enable(pDoc->CanUndo());
}

void CSameGameView::OnUpdate32771(CCmdUI *pCmdUI)
{
	//  First get a pointer to the document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Enable option if it is available
	pCmdUI->Enable(pDoc->CanRedo());
}