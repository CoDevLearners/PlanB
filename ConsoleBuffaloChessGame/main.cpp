#include <iostream>
#include <Windows.h>

#include "../BuffaloChessGameLib/BuffaloChessGameLib.h"

#include "ConsoleRender.h"


// void GameProc(ConsoleRender *pRender, IGameHandle *pGame)
// {
// 	if ( pGame->IsOver() )
// 	{
// 		return;
// 	}
// 
// 	do
// 	{
// 		Owner owner = pGame->GetTurnOwner();
// 		Cell selCell;
// 		std::vector<Action> actions;
// 		Action *pAction = nullptr;
// 
// 		do
// 		{
// 			pRender->PrintChessBoard();
// 			std::vector<Piece> pieces = pGame->GetAlivePieces();
// 			for ( const Piece &piece : pieces )
// 			{
// 				pRender->PrintPiece(piece);
// 			}
// 			pRender->PrintTurnHelp(owner);
// 
// 			do
// 			{
// 				pRender->ClearInputArea();
// 				pRender->PrintStateHelp(ConsoleRender::State::WaitInput);
// 				std::cin >> selCell.col >> selCell.row;
// 				selCell = selCell - Cell(1, 1);
// 
// 				actions = pGame->GetActions(owner, selCell);
// 			} 
// 			while ( actions.empty() );
// 
// 			for ( const Action &action : actions )
// 			{
// 				pRender->PrintHint(action);
// 			}
// 
// 
// 			pAction = nullptr;
// 			pRender->PrintStateHelp(ConsoleRender::State::WaitSelect);
// 			std::cin >> selCell.col >> selCell.row;
// 			selCell = selCell - Cell(1, 1);
// 
// 			int selIdx = -1;
// 			int numAction = actions.size();
// 			for ( int i = 0; i < numAction; ++i )
// 			{
// 				if ( actions[i].destination == selCell )
// 				{
// 					selIdx = i;
// 					break;
// 				}
// 			}
// 			if ( selIdx < 0 )
// 			{
// 				continue;
// 			}
// 			pAction = &actions[selIdx];
// 		} 
// 		while ( ( nullptr == pAction ) || !pGame->Update(*pAction) );
// 	}
// 	while ( !pGame->IsOver() );
// 
// 	pRender->PrintVictory(pGame->GetTurnOwner());
// }


int main(void)
{
	ConsoleRender *pRender = new ConsoleRender();
	IBuffaloChess *pGame = IBuffaloChess::CreateGame();

	auto info = pGame->GetPieceInfo(Cell(6, 0));
	auto hints = pGame->GetHint(info);

	return 0;
}
