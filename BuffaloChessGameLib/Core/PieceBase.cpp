#include "pch.h"

#include "PieceBase.h"
#include "BuffaloChess.h"

PieceBase::PieceBase(PieceInfo info) :
	m_pieceInfo(info), m_hints(0), m_hasCalcHint(false)
{}

PieceBase::~PieceBase()
{}

const PieceInfo *const PieceBase::GetPieceInfo()
{
	return &m_pieceInfo;
}

void PieceBase::ClearHints()
{
	if ( m_hasCalcHint )
	{
		m_hints.clear();
		m_hasCalcHint = false;
	}
}

const std::vector<ActionBase *> PieceBase::GetHints(const GameContext *const pContext)
{
	if ( !m_hasCalcHint )
	{
		CalcAction(pContext);
		m_hasCalcHint = true;
	}

	return m_hints;
}

bool PieceBase::CheckValidHint(const ActionBase *pHint)
{
	if ( !m_hasCalcHint )
	{
		return false;
	}

	for ( const ActionBase *hint : m_hints )
	{
		if ( hint == pHint )
		{
			return true;
		}
	}

	return false;
}

bool PieceBase::SetDead(GameContext *pContext)
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
	pContext->board[currCell.row][currCell.col] = nullptr;

	return false;
}
