#include "pch.h"
#include "MoveAction.h"

#include "PieceBase.h"
#include "BuffaloChess.h"

MoveAction::MoveAction(PieceBase *piece, const Cell &cell) :
    m_pPiece(piece), m_dstCell(cell)
{
    m_hint.piece = *( m_pPiece->GetPieceInfo() );
    m_hint.destination = cell;
}

bool MoveAction::Operator(const GameContext *pContext)
{
    if ( m_pPiece != pContext->GetPiece(m_dstCell) )
    {
        return false;
    }

    if ( !m_pPiece->CheckValidHint(this) )
    {
        return false;
    }

    pContext->SetPiece(m_dstCell, m_pPiece);

    return true;
}
