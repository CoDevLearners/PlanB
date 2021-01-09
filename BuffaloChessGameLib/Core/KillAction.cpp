#include "pch.h"
#include "KillAction.h"

#include "PieceBase.h"
#include "BuffaloChess.h"

KillAction::KillAction(PieceBase *pPiece, const Cell &cell, PieceBase *pDeadPiece) :
    m_pPiece(pPiece), m_dstCell(cell), m_pDeadPiece(pDeadPiece)
{
    m_hint.piece = *( m_pPiece->GetPieceInfo() );
    m_hint.destination = m_dstCell;
    m_hint.hasKill = true;
    m_hint.deadPiece = *( m_pDeadPiece->GetPieceInfo() );
}

bool KillAction::Operator(GameContext *pContext)
{
    PieceBase *pDeadPiece = pContext->GetPiece(m_dstCell);
    if ( m_pPiece == pDeadPiece )
    {
        return false;
    }

    if ( !m_pPiece->CheckValidHint(this) )
    {
        return false;
    }

    pDeadPiece->SetDead(pContext);
    m_pPiece->Move(pContext, m_dstCell);

    return true;
}
