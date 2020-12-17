#include "PieceBase.h"

PieceBase::PieceBase(Cell cell, State state /*= State::Alive*/) :
	m_position(cell),
	m_state(state)
{
}

PieceBase::~PieceBase()
{
}

Cell PieceBase::GetPosition() const
{
	return m_position;
}

PieceBase::State PieceBase::GetState() const
{
	return State();
}
