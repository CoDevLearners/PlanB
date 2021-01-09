#pragma once

#include "PieceBase.h"

class ChiefPiece : public PieceBase {

public:
	ChiefPiece(PieceInfo info);
	~ChiefPiece();

	// PieceBase��(��) ���� ��ӵ�
	virtual void CalcAction(const GameContext *const pContext) override;
};