#pragma once

#include "PieceBase.h"

class ChiefPiece : public PieceBase 
{

public:
	ChiefPiece(PieceInfo info);
	~ChiefPiece();

	// PieceBase을(를) 통해 상속됨
	virtual void CalcAction(GameContext *const pContext) override;
};