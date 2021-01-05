#include "pch.h"
#include "Common.h"


PieceId::operator uint32_t() const
{
	return key;
}

PieceId::PieceId() :
	key(-1)
{}

PieceId::PieceId(Owner owner, PieceType pieceType, uint8_t number) :
	PieceId()
{
	this->owner  = owner;
	this->type   = pieceType;
	this->number = number;
}

Piece::Piece() 
{
	id    = InvalidPieceId;
	cell  = { static_cast<uint32_t>(-1), static_cast<uint32_t>( -1 ) };
	alive = false;
}

Piece::Piece(PieceId id, Cell cell, bool alive) :
	id(id),
	cell(cell),
	alive(alive)
{}
