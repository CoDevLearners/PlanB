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