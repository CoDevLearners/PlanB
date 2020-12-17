#pragma once
#include "PieceBase.h"
class Cheif : public PieceBase
{
public:
	explicit Cheif(Cell cell);
	std::vector<Actions> GetBehavior(const Board& board) const override;
};

