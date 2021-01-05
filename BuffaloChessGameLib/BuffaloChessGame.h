#pragma once

#include "pch.h"
#include "Common.h"
#include "IGameHandle.h"

#define NUM_TOTAL_PIECE (NUM_BUFFALO + NUM_DOG + NUM_CHIEF)

using Board = PieceId[MAX_BOARD_ROW][MAX_BOARD_COL];	// 11행, 7열

enum class GameState : uint8_t {
	Invalid = static_cast<uint8_t>( -1 ),
	InGame = 0,
	GameOver,
};

class BuffaloChessGame : public IGameHandle 
{
private:
	Board m_boards;
	Piece m_pieces[NUM_TOTAL_PIECE];
	uint32_t m_numAlivePieces;
	Piece *m_alivePieces[NUM_TOTAL_PIECE];
	uint32_t m_numDeadPieces;
	Piece *m_deadPieces[NUM_TOTAL_PIECE];

	GameState m_state;
	uint32_t m_numSeq;

public:
	BuffaloChessGame();
	virtual ~BuffaloChessGame();

	// IGameHandle을(를) 통해 상속됨
	virtual bool Initalize() override;
	virtual void Release() override;
	virtual bool Update(const Action &action) override;
	virtual Piece GetPiece(const Cell &cell) override;
	virtual Piece GetPiece(const PieceId &pieceId) override;
	virtual std::vector<Action> GetActions(const Cell &cell) override;
	virtual Owner GetTurnOwner() override;
	virtual std::vector<Piece> GetAllPieces() override;
	virtual std::vector<Piece> GetAlivePieces() override;
	virtual std::vector<Piece> GetDeadPieces() override;
};

