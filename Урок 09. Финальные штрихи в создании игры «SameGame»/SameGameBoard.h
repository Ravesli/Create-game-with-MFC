#pragma once


class CSameGameBoard
{
public:
	/*  Конструктор по-умолчанию */
	CSameGameBoard(void);
	/*  Конструктор глубокого копирования */
	CSameGameBoard(const CSameGameBoard& board);
	/*  Деструктор  */
	~CSameGameBoard(void);
	/*  Функция для рандомной расстановки блоков в начале игры */
	void SetupBoard(void);
	/*  Получаем цвет в определённом участке игрового поля */
	COLORREF GetBoardSpace(int row, int col);
	/*  Геттеры для получения информации о параметрах игрового поля */
	int GetWidth(void) const { return m_nWidth; }
	void SetWidth(int nWidth)
	{	m_nWidth = (nWidth >= 3) ? nWidth : 3;	}
	int GetHeight(void) const { return m_nHeight; }
	void SetHeight(int nHeight)
	{	m_nHeight = (nHeight >= 3) ? nHeight : 3; }
	int GetColumns(void) const { return m_nColumns; }
	void SetColumns(int nColumns)
	{   m_nColumns = (nColumns >= 5) ? nColumns : 5; }
	int GetRows(void) const { return m_nRows; }
	void SetRows(int nRows)
	{	m_nRows = (nRows >= 5) ? nRows : 5;	}
	/*  Гетеры и Сеттеры для количества цветов */
	int GetNumColors(void) { return m_nColors; }
	void SetNumColors(int nColors)
	{	m_nColors = (nColors >= 3 && nColors <= 7) ? nColors : m_nColors;	}

	/*  Мы закончили игру? */
	bool IsGameOver(void) const;
	/*  Подсчет количества оставщихся блоков */
	int GetRemainingCount(void) const { return m_nRemaining; }
	/*  Функция для удаления всех примыкающих блоков */
	int DeleteBlocks(int row, int col);
	/*  Функция для удаления игрового поля и освобождения памяти */
	void DeleteBoard(void);
	
private:
	/*  Функция для создания игрового поля и выделения памяти под него */
	void CreateBoard(void);
	/*  Перечисление с вариантами направления (откуда мы пришли). Потребуется для удаления блоков */
	enum Direction
	{
		DIRECTION_UP,
		DIRECTION_DOWN,
		DIRECTION_LEFT,
		DIRECTION_RIGHT
	};
	/*  Вспомогательная рекурсивная функция для удаления примыкающих блоков */
	int DeleteNeighborBlocks(int row, int col, int color,
		Direction direction);
	/*  Функция для сжатия доски после того, как были удалены блоки */
	void CompactBoard(void);
	/*  Указатель на двумерный массив */
	int** m_arrBoard;
	/*  Список цветов, 0 – цвет фона, 1-7 - цвета блоков */
	static COLORREF m_arrColors[8];

	/*  Информация о размере игрового поля */
	int m_nColumns;
	int m_nRows;
	int m_nHeight;
	int m_nWidth;

	/*  Количество оставшихся блоков */
	int m_nRemaining;
	/*  Количество цветов */
	int m_nColors;

};

