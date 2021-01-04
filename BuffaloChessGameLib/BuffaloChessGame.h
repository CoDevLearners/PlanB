#pragma once

#include "Common.h"
#include "IGameHandle.h"
#include <map>

class BuffaloChessGame : public IGameHandle 
{
private:
	GameState m_state;
	std::map<PieceId, int> m_pieces;
	uint32_t m_numSeq;
	Board m_boards;

public:
	BuffaloChessGame();
	virtual ~BuffaloChessGame();

	// IGameHandle을(를) 통해 상속됨
	virtual bool Initalize() override;
	virtual void Release() override;
	virtual bool Update(IAction *pAction, UpdateHandler hUpdate = nullptr) override;
	virtual std::vector<Cell> GetHint(const Cell &cell) override;
	virtual Owner GetTurnOwner() override;

};

