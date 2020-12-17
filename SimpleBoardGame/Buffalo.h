#pragma once
#include "PieceBase.h"

class Buffalo : public PieceBase
{
public:
	explicit Buffalo(Cell cell);
	std::vector<Actions> GetBehavior(const Board& board) const override;
};

