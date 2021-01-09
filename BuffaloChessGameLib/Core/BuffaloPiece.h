#pragma once

#include "PieceBase.h"

class BuffaloPiece : public PieceBase 
{

public:
	BuffaloPiece(PieceInfo info);
	virtual ~BuffaloPiece();

	// PieceBase을(를) 통해 상속됨
	virtual void CalcAction(GameContext *const pContext) override;
};
