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

	virtual bool Update(Action *pAction) = 0;
	virtual Piece GetPiece(const Cell& cell) = 0;
	virtual Piece GetPiece(const PieceId& pieceId) = 0;
	virtual std::vector<Action> GetActions(const Cell &cell) = 0;
	virtual Owner GetTurnOwner() = 0;
	virtual std::vector<Piece> GetPieces() = 0;
	virtual std::vector<Piece> GetAlivePieces() = 0;
	virtual std::vector<Piece> GetDeadPieces() = 0;
};