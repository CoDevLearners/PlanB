#pragma once

#include "PieceBase.h"

class DogPiece : public PieceBase 
{


public:
	DogPiece(PieceInfo info);
	virtual ~DogPiece();

	// PieceBase��(��) ���� ��ӵ�
	virtual void CalcAction(GameContext *const pContext) override;
};