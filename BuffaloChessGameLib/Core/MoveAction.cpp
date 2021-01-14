#include "Common.h"
#include "MoveAction.h"

#include "PieceBase.h"
#include "BuffaloChess.h"

MoveAction::MoveAction(PieceBase *pPiece, const Cell &cell) :
    m_pPiece(pPiece), m_dstCell(cell)
{
    m_hint.piece = *( m_pPiece->GetPieceInfo() );
    m_hint.destination = cell;
}

bool MoveAction::Operator(GameContext *pContext)
{
    if ( nullptr != pContext->GetPiece(m_dstCell) )
    {
        return false;
    }

    if ( !m_pPiece->CheckValidHint(this) )
    {
        return false;
    }

    return m_pPiece->Move(pContext, m_dstCell);
}
