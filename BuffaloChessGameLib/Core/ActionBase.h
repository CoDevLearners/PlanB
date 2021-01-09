#pragma once

#include "Common.h"

struct GameContext;

class ActionBase {
protected:
	Action m_hint;

public:
	ActionBase();
	virtual ~ActionBase();

	virtual bool Operator(GameContext *pContext) = 0;

	virtual const Action * const GetHint();
};