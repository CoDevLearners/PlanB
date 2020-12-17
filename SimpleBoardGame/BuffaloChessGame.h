#pragma once
#include "Common.h"
#include "Board.h"
#include "PieceBase.h"

class BuffaloChessGame
{
	uint32_t m_turn; // 1∫Œ≈Õ º¡¥œ¥Ÿ. 0≈œ¿Ã πº¥œ±Ó? 
	Board m_board;
	std::map<PieceID, PieceBase*> m_pieces;

public:
	bool Initalize();
	const std::vector<Actions> GetActions(PieceID pieceID);
	bool Update(const Actions& behavior);

private:
	bool InitPieces();
	bool InitBoard();
};