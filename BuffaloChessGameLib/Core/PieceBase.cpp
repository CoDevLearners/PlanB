#include "pch.h"

#include "PieceBase.h"
#include "BuffaloChess.h"

PieceBase::PieceBase(PieceInfo info) :
	m_pieceInfo(info), m_hints(0)
{}

PieceBase::~PieceBase()
{}

const PieceInfo *const PieceBase::GetPieceInfo()
{
	return &m_pieceInfo;
}

const std::vector<ActionBase *> PieceBase::GetHints(GameContext *const pContext)
{
	CalcAction(pContext);

	return m_hints;
}

bool PieceBase::CheckValidHint(const ActionBase *pHint)
{
	for ( const ActionBase *hint : m_hints )
	{
		if ( hint == pHint )
		{
			return true;
		}
	}

	return false;
}

bool PieceBase::SetDead(GameContext * const pContext)
{
	if ( nullptr == pContext )
	{
		return false;
	}
	if ( false == m_pieceInfo.isAlive )
	{
		return true;
	}

	m_pieceInfo.isAlive = false;
	const Cell &currCell = m_pieceInfo.cell;
	pContext->SetPiece(currCell, nullptr);

	return true;
}

bool PieceBase::Move(GameContext *pContext, const Cell &cell)
{
	if ( nullptr == pContext )
	{
		return false;
	}
	if ( false == m_pieceInfo.isAlive )
	{
		return false;
	}
	if ( nullptr != pContext->GetPiece(cell) )
	{
		return false;
	}

	pContext->SetPiece(m_pieceInfo.cell, nullptr);
	m_pieceInfo.cell = cell;
	pContext->SetPiece(cell, this);

	return true;
}
