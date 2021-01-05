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
};

