#include <iostream>
#include <Windows.h>

#include "../BuffaloChessGameLib/BuffaloChessGameLib.h"

#include "ConsoleRender.h"


void GameProc(ConsoleRender *pRender, IBuffaloChess *pGame)
{
	if ( pGame->IsGameOver() )
	{
		return;
	}

	while( !pGame->IsGameOver() )
	{
		PlayerType player = pGame->GetPlayerThisTurn();
		PieceInfo selPiece;
		Cell selCell;
		Action *pSelAction = nullptr;

		do
		{
			pRender->PrintChessBoard();
			std::vector<PieceInfo> pieces = pGame->GetAlivePieces();
			for ( const PieceInfo &piece : pieces )
			{
				pRender->PrintPiece(piece);
			}
			pRender->PrintTurnHelp(player);

			do
			{
				pRender->ClearInputArea();
				pRender->PrintStateHelp(ConsoleRender::State::WaitInput);
				std::cin >> selCell.col >> selCell.row;
				selCell = selCell - Cell(1, 1);

				selPiece = pGame->GetPieceInfo(selCell);
			} 
			while ( selPiece.owner != player );

			const std::vector<Action *> actions = pGame->GetHint(selPiece);

			for ( const Action * action : actions )
			{
				pRender->PrintHint(*action);
			}

			pSelAction = nullptr;
			pRender->PrintStateHelp(ConsoleRender::State::WaitSelect);
			std::cin >> selCell.col >> selCell.row;
			selCell = selCell - Cell(1, 1);

			int selIdx = -1;
			int numAction = actions.size();
			for ( int i = 0; i < numAction; ++i )
			{
				if ( actions[i]->destination == selCell )
				{
					selIdx = i;
					break;
				}
			}
			if ( selIdx < 0 )
			{
				continue;
			}
			pSelAction = actions[selIdx];
		} 
		while ( ( nullptr == pSelAction ) || !pGame->Update(pSelAction) );
	}
	switch ( pGame->GetPlayerThisTurn() )
	{
	case PlayerType::Grass:
		pRender->PrintVictory(PlayerType::River);
		break;
	case PlayerType::River:
		pRender->PrintVictory(PlayerType::Grass);
		break;
	default:
		break;
	}
}


int main(void)
{
	ConsoleRender *pRender = new ConsoleRender();
	IBuffaloChess *pGame = IBuffaloChess::CreateGame();

	GameProc(pRender, pGame);

	return 0;
}
