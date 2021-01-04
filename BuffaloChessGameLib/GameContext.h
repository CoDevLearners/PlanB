#pragma once

#include "Common.h"

class IAction;

struct GameContext {
	Board board;
	void  *pUserData;
};

