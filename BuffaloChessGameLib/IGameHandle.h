#pragma once

#include <vector>

class IAction;
struct Cell;
struct GameInfo;

struct GameContext;
typedef void ( *InitHandler )( GameContext *pContext, void *pUserData );
typedef void ( *UpdateHandler )( GameContext *pContext );
typedef void ( *GetBoardInfoHandler )( GameContext *pContext );

class IGameHandle {
public:
	static IGameHandle* CreateGame();

	virtual ~IGameHandle()
	{}

	virtual bool Initalize() = 0;
	virtual void Release() = 0;

	virtual bool Update(IAction *pAction, UpdateHandler hUpdate = nullptr) = 0;
	virtual std::vector<Cell> GetHint(const Cell &cell) = 0;
	virtual Owner GetTurnOwner() = 0;
};