#pragma once

#include "PieceBase.h"

class BuffaloPiece : public PieceBase 
{

public:
	BuffaloPiece(PieceInfo info);
	virtual ~BuffaloPiece();

	// PieceBase��(��) ���� ��ӵ�
	virtual void CalcAction(GameContext *const pContext) override;
};
