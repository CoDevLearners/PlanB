#pragma once

#include "ActionBase.h"

class MoveAction : ActionBase {
protected:


public:

	// ActionBase��(��) ���� ��ӵ�
	virtual bool Operator(const GameContext *pContext) override;
};