#include "Common.h"


Cell::Cell() :
	row(0),
	col(0)
{}

Cell::Cell(uint32_t row, uint32_t col) :
	row(row),
	col(col)
{}

Cell operator+(const Cell& lhs, const Cell& rhs)
{
	return Cell(lhs.row + rhs.row, lhs.col + rhs.col);
}

Cell operator-(const Cell& lhs, const Cell& rhs)
{
	return Cell(lhs.row - rhs.row, lhs.col - rhs.col);
}

Cell operator*(const int& lhs, const Cell& rhs)
{
	return Cell(lhs * rhs.row, lhs * rhs.col);
}

Cell operator*(const Cell &lhs, const int &rhs)
{
	return Cell(rhs * lhs.row, rhs * lhs.col);
}

bool operator==(const Cell& lhs, const Cell& rhs)
{
	return ( ( lhs.row == rhs.row ) && ( lhs.col == rhs.col ) );
}

bool operator==(const PieceInfo &lhs, const PieceInfo &rhs)
{
	return ( 0 == memcmp(&lhs, &rhs, sizeof(PieceInfo)) );
}

PieceInfo::PieceInfo() :
	PieceInfo(PlayerType::None, PieceType::None, 0, false, Cell())
{}

PieceInfo::PieceInfo(PlayerType owner, PieceType type, PieceId id, bool isAlive, Cell cell) :
	owner(owner), type(type), id(id), isAlive(isAlive), cell(cell)
{}

Action::Action() :
	piece(), destination(), hasKilled(false), deadPiece(), hasWon(false), player(PlayerType::None)
{}
