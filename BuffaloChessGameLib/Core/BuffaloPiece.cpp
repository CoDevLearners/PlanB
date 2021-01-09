#include "pch.h"
#include "BuffaloPiece.h"
#include "BuffaloChess.h"
#include "MoveAction.h"

BuffaloPiece::BuffaloPiece(PieceInfo info) :
    PieceBase(info)
{}

BuffaloPiece::~BuffaloPiece()
{}

void BuffaloPiece::CalcAction(const GameContext *const pContext)
{
    if ( m_hasCalcHint )
    {
        return;
    }

    const Cell &currCell = m_pieceInfo.cell;
    const Cell &nextCell = currCell - Cell(1, 0);

    if ( !m_pieceInfo.isAlive ||
         ( nullptr != pContext->GetPiece(nextCell) ) )
    {
        m_hints.clear();
        m_hasCalcHint = true;

        return;
    }

    ActionBase *pAction = (ActionBase *)( new MoveAction(this, nextCell) );
    m_hints.push_back(pAction);
    m_hasCalcHint = true;

    return;
}
