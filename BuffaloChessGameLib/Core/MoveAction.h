#pragma once

#include "ActionBase.h"

class PieceBase;

class MoveAction : ActionBase {
protected:
	PieceBase *m_pPiece;
	Cell m_dstCell;

public:
	MoveAction(PieceBase *piece, const Cell &cell);

	// ActionBase��(��) ���� ��ӵ�
	virtual bool Operator(const GameContext *pContext) override;
};