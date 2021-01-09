#pragma once

#include "Common.h"

struct GameContext;

class ActionBase : IHint {
protected:
	PieceInfo *m_pPieceInfo;
	Cell m_destination;

public:
	ActionBase(PieceInfo * const info, const Cell &dst);
	virtual ~ActionBase();

	virtual bool Operator(const GameContext *pContext) = 0;


	// IHint��(��) ���� ��ӵ�
	virtual const PieceInfo &GetPieceInfo() override;

	virtual const Cell &GetDestination() override;

};