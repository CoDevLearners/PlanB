#pragma once

#include "Common.h"

#include "pch.h"

class ActionBase;
struct GameContext;

class PieceBase {
protected:
	PieceInfo m_pieceInfo;
	bool m_hasCalcHint;
	std::vector<ActionBase *> m_hints;

public:
	PieceBase(PieceInfo info);
	virtual ~PieceBase();

	const PieceInfo *const GetPieceInfo();

	virtual void ClearHints();

	virtual const std::vector<ActionBase *> GetHints(GameContext *const pContext);

	virtual bool CheckValidHint(const ActionBase *pHint);

	virtual void CalcAction(GameContext *const pContext) = 0;

	virtual bool SetDead(GameContext *pContext);

	virtual bool Move(GameContext *pContext, const Cell &cell);
};