#pragma once

#include "PieceBase.h"

class BuffaloPiece : public PieceBase 
{

public:
	BuffaloPiece(PieceInfo info);
	virtual ~BuffaloPiece();

	// PieceBase��(��) ���� ��ӵ�
	virtual void CalcAction(const GameContext *const pContext) override;
};
