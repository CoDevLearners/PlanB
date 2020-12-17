#pragma once

#include "Common.h"

class Board
{
public:
	static constexpr uint32_t MAX_COL = 7;
	static constexpr uint32_t MAX_ROW = 11;

private:
	PieceID m_board[MAX_ROW][MAX_COL]; // 11За, 7ї­

public:
	Board();
	virtual ~Board();
	bool GetPiece(const Cell& cell, PieceID& outPirceID) const;
	bool SetPiece(const Cell& cell, PieceID pieceID);

private:
	bool IsInBoard(const Cell& cell) const;
};
