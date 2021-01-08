#include "pch.h"
#include "BuffaloChessGameLib.h"
#include "BuffaloChessGame.h"

IGameHandle *CreateBuffaloChessGame()
{
	return dynamic_cast<IGameHandle *>( new BuffaloChessGame() );
}
