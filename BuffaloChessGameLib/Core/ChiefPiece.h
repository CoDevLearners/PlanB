#pragma once

#include "PieceBase.h"

class ChiefPiece : public PieceBase 
{

public:
	ChiefPiece(PieceInfo info);
	~ChiefPiece();

	// PieceBase��(��) ���� ��ӵ�
	virtual void CalcAction(GameContext *const pContext) override;
};