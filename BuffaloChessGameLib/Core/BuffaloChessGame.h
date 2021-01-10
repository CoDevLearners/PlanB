#pragma once

#include "pch.h"
#include "Common.h"
#include "IGameHandle.h"

#define NUM_TOTAL_PIECE (NUM_BUFFALO + NUM_DOG + NUM_CHIEF)

using Board = PieceId[MAX_BOARD_ROW][MAX_BOARD_COL];	// 11행, 7열

enum class GameState : uint8_t {
	Invalid = 0xff,
	Ready = 0x00,
	InGame,
	GameOver,
};

class BuffaloChessGame : public IGameHandle 
{
private:
	Board m_boards;
	std::vector<Piece> m_pieceArr;
	std::set<Piece *> m_alivePiecePtrs;
	std::set<Piece *> m_deadPiecePtrs;

	GameState m_state;
	uint32_t m_numSeq;

	static constexpr uint32_t NumDir = 8;
	static const Cell Dir[NumDir];

	void MakeBoardClean();
	void GenAllGrassPiece();
	void GenAllRiverPiece();

	void SetDeadPiece(const PieceId &id);
	void SetAlivePieve(const PieceId &id);
	void MovePiece(const PieceId &id, const Cell &cell);

	bool InBoard(const Cell &cell);
	bool EmptyCell(const Cell &cell);
	PieceId GetPieceId(const Cell &cell);

	bool ExistMovableBuffalo(const PieceId &exceptPiece = InvalidPieceId);
	bool BuffaloHasArrived();

	void CalcBuffaloAction(const Piece &piece, std::vector<Action> &actions);
	void CalcDogAction(const Piece &piece, std::vector<Action> &actions);
	void CalcChiefAction(const Piece &piece, std::vector<Action> &actions);

public:
	BuffaloChessGame();
	virtual ~BuffaloChessGame();

	// IGameHandle을(를) 통해 상속됨
	virtual bool Initalize() override;
	virtual void Release() override;
	virtual bool Update(const Action &action) override;
	virtual Piece GetPiece(const Cell &cell) override;
	virtual Piece GetPiece(const PieceId &pieceId) override;
	virtual std::vector<Action> GetActions(const Owner &owner, const Cell &cell) override;
	virtual Owner GetTurnOwner() override;
	virtual std::vector<Piece> GetAllPieces() override;
	virtual std::vector<Piece> GetAlivePieces() override;
	virtual std::vector<Piece> GetDeadPieces() override;
	virtual bool IsOver() override;
};

