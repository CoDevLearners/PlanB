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


	// IHint을(를) 통해 상속됨
	virtual const PieceInfo &GetPieceInfo() override;

	virtual const Cell &GetDestination() override;

};