#include "pch.h"
#include "BuffaloChessGameLib.h"
#include "BuffaloChessGame.h"

IGameHandle *IGameHandle::CreateGame()
{
	return new BuffaloChessGame();
}
