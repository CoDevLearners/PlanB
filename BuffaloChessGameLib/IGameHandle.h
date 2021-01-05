#pragma once

#include "pch.h"
#include "Common.h"

__interface IGameHandle 
{
	virtual bool Initalize() = 0;
	virtual void Release() = 0;

	virtual bool Update(const Action &action) = 0;
	virtual Piece GetPiece(const Cell& cell) = 0;
	virtual Piece GetPiece(const PieceId& pieceId) = 0;
	virtual std::vector<Action> GetActions(const Cell &cell) = 0;
	virtual Owner GetTurnOwner() = 0;
	virtual std::vector<Piece> GetAllPieces() = 0;
	virtual std::vector<Piece> GetAlivePieces() = 0;
	virtual std::vector<Piece> GetDeadPieces() = 0;
};