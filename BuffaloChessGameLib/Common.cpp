#include "pch.h"
#include "Common.h"


PieceId::operator uint32_t() const
{
	return key;
}

PieceId::PieceId() :
	key(-1)
{}

PieceId::PieceId(Owner owner, PieceType pieceType, uint16_t number) 
{
	this->owner  = owner;
	this->type   = pieceType;
	this->number = number;
}

Piece::Piece() :
	alive(false)
{}

Piece::Piece(PieceId id, Cell cell, bool alive) :
	id(id),
	cell(cell),
	alive(alive)
{}

Cell::Cell() :
	row(0),
	col(0)
{}

Cell::Cell(uint32_t row, uint32_t col) :
	row(row),
	col(col)
{}

Cell operator+(const Cell &lhs, const Cell &rhs)
{
	return Cell(lhs.row + rhs.row, lhs.col + rhs.col);
}

Cell operator-(const Cell &lhs, const Cell &rhs)
{
	return Cell(lhs.row - rhs.row, lhs.col - rhs.col);
}

bool operator==(const Cell &lhs, const Cell &rhs)
{
	return ( ( lhs.row == rhs.row ) && ( lhs.col == rhs.col ) );
}

Action::Action() :
	piece(),
	destination(),
	hasKilled(false),
	deadPiece(),
	hasWon(false),
	owner(Owner::Invalid)
{}
