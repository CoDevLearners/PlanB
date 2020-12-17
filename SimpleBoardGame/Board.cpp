#include "Board.h"
#include "PieceBase.h"


Board::Board()
{
}

Board::~Board()
{
}

bool Board::GetPiece(const Cell& cell, PieceID& outPirceID) const
{
	if (!IsInBoard(cell))
	{
		return false;
	}

	outPirceID = m_board[cell.row][cell.col];
	return true;
}

bool Board::SetPiece(const Cell& cell, PieceID pieceID)
{
	if (!IsInBoard(cell))
	{
		return false;
	}

	m_board[cell.row][cell.col] = pieceID;
	return true;
}

bool Board::IsInBoard(const Cell& cell) const
{
	return (cell.row >= MAX_ROW || cell.col >= MAX_COL);
}
