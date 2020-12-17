#include "Dog.h"

Dog::Dog(Cell cell) :
	PieceBase(cell)
{
}

std::vector<Actions> Dog::GetBehavior(const Board& board) const
{
	throw std::logic_error("The method or operation is not implemented.");
}
