#pragma once

#include "ActionBase.h"

class PieceBase;

class MoveAction : ActionBase {
protected:
	PieceBase *m_pPiece;
	Cell m_dstCell;

public:
	MoveAction(PieceBase *pPiece, const Cell &cell);

	// ActionBase��(��) ���� ��ӵ�
	virtual bool Operator(GameContext *pContext) override;
};