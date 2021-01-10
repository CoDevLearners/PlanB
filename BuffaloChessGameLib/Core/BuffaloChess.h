#pragma once

#include "Common.h"
#include "IBuffaloChess.h"

class PieceBase;

struct GameContext {
	const uint8_t boardRow;
	const uint8_t boardCol;
	
	GameState gameState;
	uint64_t turnNumber;

	PieceBase ***board;

	GameContext(uint8_t row, uint8_t col);
	~GameContext();

	PieceBase* GetPiece(const Cell &cell) const;
	void SetPiece(const Cell &cell, PieceBase *const piece) const;

	bool InBoard(const Cell &cell) const;
};

class BuffaloChess : public IBuffaloChess {
private:
	GameContext *m_pGameContext;
	
	std::vector<PieceBase *> m_pieces;

	void GenPieces();
	void GenGrassPiece();
	void GenRiverPiece();

public:
	
	BuffaloChess();
	virtual ~BuffaloChess();

	PieceBase *GetPiece(const PieceInfo &info);

	// IBuffaloChess을(를) 통해 상속됨
	virtual Cell GetBoardSize() override;

	virtual bool IsGameOver() override;

	virtual PlayerType GetPlayerThisTurn() override;

	virtual PieceInfo GetPieceInfo(const Cell &cell) override;

	virtual const std::vector<Action *> GetHint(const PieceInfo &pieceInfo) override;

	virtual bool Update(const Action *pHint) override;

	virtual std::vector<PieceInfo> GetAllPieces() override;

	virtual std::vector<PieceInfo> GetAlivePieces() override;

	virtual std::vector<PieceInfo> GetDeadPieces() override;

	PieceBase *GetBuffaloArrivintAtRiver();

	bool ExistMovingBuffalo();
};