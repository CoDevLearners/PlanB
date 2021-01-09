#include "pch.h"
#include "ActionBase.h"

ActionBase::ActionBase(PieceInfo * const info, const Cell &dst) :
	m_pPieceInfo(info), m_destination(dst)
{}

ActionBase::~ActionBase()
{}

const PieceInfo &ActionBase::GetPieceInfo()
{
	return *m_pPieceInfo;
}

const Cell &ActionBase::GetDestination()
{
	return m_destination;
}
