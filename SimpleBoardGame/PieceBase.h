#pragma once
#include "Common.h"

class Board;

class PieceBase
{
protected:
	enum class State
	{
		Alive,
		Dead
	};

protected:
	Cell m_position;
	State m_state;

public:
	PieceBase(Cell cell, State state = State::Alive);
	virtual ~PieceBase();
	virtual std::vector<Actions> GetBehavior(const Board& board) const = 0;

	Cell GetPosition() const;
	State GetState() const;
};
