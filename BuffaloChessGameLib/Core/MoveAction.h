#pragma once

#include "ActionBase.h"

class MoveAction : ActionBase {
protected:


public:

	// ActionBase을(를) 통해 상속됨
	virtual bool Operator(const GameContext *pContext) override;
};