#include "Cheif.h"
#include "Board.h"

Cheif::Cheif(Cell cell) : PieceBase(cell)
{
}

std::vector<Actions> Cheif::GetBehavior(const Board& board) const
{
	std::vector<Actions> behaviors;
    return behaviors;
}
