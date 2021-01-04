#pragma once

struct GameContext;

class IAction {
public:
	virtual void Operate() = 0;
};

