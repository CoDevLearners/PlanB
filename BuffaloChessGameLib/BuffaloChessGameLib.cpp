#include "pch.h"
#include "BuffaloChessGameLib.h"
#include "BuffaloChessGame.h"

BuffaloChessGame *pBuffaloChessGame = new BuffaloChessGame();

IGameHandle *GetBuffaloChessGameHandle()
{
	return dynamic_cast<IGameHandle *>( pBuffaloChessGame );
}
