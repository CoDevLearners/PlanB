#include "Buffalo.h"

Buffalo::Buffalo(Cell cell) :
	PieceBase(cell)
{
}

std::vector<Actions> Buffalo::GetBehavior(const Board& board) const
{
	throw std::logic_error("The method or operation is not implemented.");
}
