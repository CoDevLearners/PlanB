#pragma once
#include "PieceBase.h"

class Dog : public PieceBase
{
public:
	explicit Dog(Cell cell);
	std::vector<Actions> GetBehavior(const Board& board) const override;
};

