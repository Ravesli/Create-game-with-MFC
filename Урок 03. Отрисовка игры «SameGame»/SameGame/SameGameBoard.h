#pragma once

class CSameGameBoard
{
public:
	/*  Default Constructor */
	CSameGameBoard(void);
	/*  Destructor */
	~CSameGameBoard(void);
	/*  Function to randomly setup the board */
	void SetupBoard(void);
	/*  Get the color at a particular location */
	COLORREF GetBoardSpace(int row, int col);
	/*  Accessor functions to get board size information */
	int GetWidth(void) const { return m_nWidth; }
	int GetHeight(void) const { return m_nHeight; }
	int GetColumns(void) const { return m_nColumns; }
	int GetRows(void) const { return m_nRows; }
	/*  Function to delete the board and free memory */
	void DeleteBoard(void);
private:
	/*  Function to create the board and allocate memory */
	void CreateBoard(void);
	/*  2D array pointer */
	int** m_arrBoard;
	/*  List of colors, 0 is background and 1-3 are piece colors */
	COLORREF m_arrColors[4];
	/*  Board size information */
	int m_nColumns;
	int m_nRows;
	int m_nHeight;
	int m_nWidth;
};