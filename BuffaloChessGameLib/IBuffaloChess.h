#pragma once

#include "pch.h"

#include "Common.h"


class IBuffaloChess {
public:
	virtual ~IBuffaloChess()
	{}

	static IBuffaloChess *CreateGame();

	virtual Cell GetBoardSize() = 0;
	virtual bool IsGameOver() = 0;
	virtual PlayerType GetPlayerThisTurn() = 0;

	virtual PieceInfo GetPieceInfo(const Cell &cell) = 0;
	virtual const std::vector<Action *> GetHint(const PieceInfo &pieceInfo) = 0;
	virtual bool Update(const Action *pHint) = 0;

	virtual std::vector<PieceInfo> GetAllPieces() = 0;
	virtual std::vector<PieceInfo> GetAlivePieces() = 0;
	virtual std::vector<PieceInfo> GetDeadPieces() = 0;
};
