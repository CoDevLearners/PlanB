#pragma once

#include "PieceBase.h"

class DogPiece : public PieceBase 
{


public:
	DogPiece(PieceInfo info);
	virtual ~DogPiece();

	// PieceBase을(를) 통해 상속됨
	virtual void CalcAction(const GameContext *const pContext) override;
};