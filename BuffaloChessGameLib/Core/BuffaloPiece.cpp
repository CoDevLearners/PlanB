#include "pch.h"
#include "BuffaloPiece.h"
#include "BuffaloChess.h"
#include "MoveAction.h"

BuffaloPiece::BuffaloPiece(PieceInfo info) :
    PieceBase(info)
{}

BuffaloPiece::~BuffaloPiece()
{}

void BuffaloPiece::CalcAction(GameContext *const pContext)
{
    if ( !m_pieceInfo.isAlive )
    {
        return;
    }

    m_hints.clear();

    const Cell &currCell = m_pieceInfo.cell;
    const Cell &nextCell = currCell - Cell(1, 0);

    PieceBase *pDstPiece = pContext->GetPiece(nextCell);

    if ( nullptr != pDstPiece )
    {
        return;
    }

    ActionBase *pAction = (ActionBase *)( new MoveAction(this, nextCell) );
    m_hints.push_back(pAction);

    return;
}
