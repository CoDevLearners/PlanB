#pragma once

#include "../BuffaloChessGameLib/BuffaloChessGameLib.h"

class ConsoleBuffaloCessGame 
{
private:
	IGameHandle *pGameHandler;

public:
	ConsoleBuffaloCessGame();
	virtual ~ConsoleBuffaloCessGame();

	void GameProc();
};

