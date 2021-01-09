#pragma once

#include "ActionBase.h"

class PieceBase;

class KillAction : ActionBase 
{
protected:
	PieceBase *m_pPiece;
	Cell m_dstCell;
	PieceBase *m_pDeadPiece;

public:
	KillAction(PieceBase *pPiece, const Cell &cell, PieceBase *pDeadPiece);

	// ActionBase��(��) ���� ��ӵ�
	virtual bool Operator(GameContext *pContext) override;
};