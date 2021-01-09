#pragma once

#include "ActionBase.h"

class PieceBase;

class MoveAction : ActionBase {
protected:
	PieceBase *m_pPiece;
	Cell m_dstCell;

public:
	MoveAction(PieceBase *piece, const Cell &cell);

	// ActionBase을(를) 통해 상속됨
	virtual bool Operator(const GameContext *pContext) override;
};