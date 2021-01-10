#include "pch.h"
#include "DogPiece.h"
#include "BuffaloChess.h"
#include "MoveAction.h"

DogPiece::DogPiece(PieceInfo info) :
	PieceBase(info)
{}

DogPiece::~DogPiece()
{}

void DogPiece::CalcAction(GameContext *const pContext)
{
    if ( !m_pieceInfo.isAlive )
    {
        return;
    }

    m_hints.clear();

    const Cell &currCell = m_pieceInfo.cell;
    const size_t numDir = 8;
    const Cell dirCell[] = {
        Cell( 1, -1), Cell( 1, 0), Cell( 1, 1),
        Cell( 0, -1), /* Center */ Cell( 0, 1),
        Cell(-1, -1), Cell(-1, 0), Cell(-1, 1),
    };

    for ( size_t d = 0; d < numDir; ++d )
    {
        int step = 1;
        while(true)
        {
            const Cell &nextCell = currCell + ( step * dirCell[d] );
            if ( !pContext->InBoard(nextCell) )
            {
                break;
            }

            PieceBase *pDstPiece = pContext->GetPiece(nextCell);

            if ( nullptr == pDstPiece )
            {
                ActionBase *pAction = (ActionBase *)( new MoveAction(this, nextCell) );
                m_hints.push_back(pAction);
            }
            else
            {
                break;
            }
            ++step;
        }
    }
}
