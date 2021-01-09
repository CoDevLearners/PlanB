#include "pch.h"

#include "Common.h"

#include "BuffaloChess.h"

#include "ActionBase.h"
#include "BuffaloPiece.h"
#include "DogPiece.h"
#include "ChiefPiece.h"


#define MAX_BOARD_ROW	7
#define MAX_BOARD_COL	11
#define NUM_BUFFALO		(11)
#define NUM_DOG			(4)
#define NUM_CHIEF		(1)
#define RIVER_ROW		(0)
#define NUM_TOTAL_PIECE	(NUM_BUFFALO + NUM_DOG + NUM_CHIEF)

IBuffaloChess *IBuffaloChess::CreateGame()
{
	return ( new BuffaloChess() );
}


void BuffaloChess::GenPieces()
{
	m_alivePieceIndex.clear();
	m_deadPieceIndex.clear();

	for ( size_t i = 0; i < NUM_TOTAL_PIECE; ++i )
	{
		delete m_pieces[i];
	}

	GenGrassPiece();
	GenRiverPiece();

	for ( size_t i = 0; i < NUM_TOTAL_PIECE; ++i )
	{
		m_alivePieceIndex.insert(i);
	}
}

void BuffaloChess::GenGrassPiece()
{
	int buffaloArrOffset = 0;
	int boardColOffset = ( MAX_BOARD_COL - NUM_BUFFALO ) / 2;
	int buffaloRow = MAX_BOARD_ROW - 1;

	for ( int number = 0; number < NUM_BUFFALO; ++number )
	{
		PieceId id = 1 + number;

		uint32_t col = boardColOffset + number;
		Cell cell = Cell(buffaloRow, col);

		uint32_t pieceArrIdx = buffaloArrOffset + number;
		// set piece
		m_pieces[pieceArrIdx] = new BuffaloPiece(PieceInfo(PlayerType::Grass, PieceType::Buffalo, id, true, cell));
		m_pGameContext->SetPiece(cell, m_pieces[pieceArrIdx]);
	}
}

void BuffaloChess::GenRiverPiece()
{
	int dogArrOffset = NUM_BUFFALO;
	int chiefArrOffset = ( NUM_BUFFALO + NUM_DOG );
	int boardColOffset = ( MAX_BOARD_COL - ( NUM_DOG + NUM_CHIEF ) ) / 2;
	int cheifRow = RIVER_ROW + 1;

	const int halfNumDog = NUM_DOG / 2;

	for ( int number = 0; number < NUM_DOG; ++number )
	{
		PieceId id = 1 + NUM_BUFFALO + number;

		uint32_t col = boardColOffset + ( NUM_CHIEF * ( halfNumDog > number ? 0 : 1 ) ) + number;
		Cell cell = Cell(cheifRow, col);

		uint32_t pieceArrIdx = dogArrOffset + number;
		// set piece
		m_pieces[pieceArrIdx] = new DogPiece(PieceInfo(PlayerType::River, PieceType::Dog, id, true, cell));
		m_pGameContext->SetPiece(cell, m_pieces[pieceArrIdx]);
	}

	// Chief
	for ( uint32_t number = 0; number < NUM_CHIEF; ++number )
	{
		PieceId id = 1 + NUM_BUFFALO + NUM_DOG + number;

		uint32_t col = boardColOffset + halfNumDog + number;
		Cell cell = Cell(cheifRow, boardColOffset + number);

		uint32_t pieceArrIdx = chiefArrOffset + number;
		// set piece
		m_pieces[pieceArrIdx] = new ChiefPiece(PieceInfo(PlayerType::River, PieceType::Chief, id, true, cell));
		m_pGameContext->SetPiece(cell, m_pieces[pieceArrIdx]);
	}

}

BuffaloChess::BuffaloChess() :
	m_pGameContext(new GameContext(MAX_BOARD_ROW, MAX_BOARD_COL)),
	m_pieces(NUM_TOTAL_PIECE)
{
	GenPieces();
}

BuffaloChess::~BuffaloChess()
{
	delete m_pGameContext;
	for ( size_t i = 0; i < NUM_TOTAL_PIECE; ++i )
	{
		delete m_pieces[i];
	}
}

PieceBase *BuffaloChess::GetPiece(const PieceInfo &info)
{
	for ( PieceBase *piece : m_pieces )
	{
		const PieceInfo *pInfo = piece->GetPieceInfo();
		if ( *pInfo == info )
		{
			return piece;
		}
	}

	return nullptr;
}

Cell BuffaloChess::GetBoardSize()
{
	return Cell(m_pGameContext->boardRow, m_pGameContext->boardCol);
}

bool BuffaloChess::IsGameOver()
{
	return ( m_pGameContext->gameState == GameState::GameOver );
}

PlayerType BuffaloChess::GetPlayerThisTurn()
{
	bool isRiver = ( m_pGameContext->turnNumber % 2 );

	return ( isRiver ? PlayerType::River : PlayerType::Grass );
}

PieceInfo BuffaloChess::GetPieceInfo(const Cell &cell)
{
	PieceBase *pPiece = m_pGameContext->board[cell.row][cell.col];

	return *( pPiece->GetPieceInfo() );
}

const std::vector<Action *> BuffaloChess::GetHint(const PieceInfo &pieceInfo)
{
	const Cell &cell = pieceInfo.cell;
	PieceBase *pPiece = m_pGameContext->GetPiece(cell);

	const std::vector<ActionBase *> actions = pPiece->GetHints(m_pGameContext);

	std::vector<Action *> res;
	for ( ActionBase* action : actions )
	{
		Action *pHint = const_cast<Action *>( action->GetHint() );
		res.push_back(pHint);
	}

	return res;
}

bool BuffaloChess::Update(const Action *pHint)
{
	// TODO : update

	return false;
}

std::vector<PieceInfo> BuffaloChess::GetAllPieces()
{
	std::vector<PieceInfo> res;
	for ( PieceBase *piece : m_pieces )
	{
		res.push_back(*( piece->GetPieceInfo() ));
	}

	return res;
}

std::vector<PieceInfo> BuffaloChess::GetAlivePieces()
{
	return std::vector<PieceInfo>();
}

std::vector<PieceInfo> BuffaloChess::GetDeadPieces()
{
	return std::vector<PieceInfo>();
}

PieceBase *BuffaloChess::GetBuffaloArrivintAtRiver()
{
	for ( size_t i = 0; i < NUM_BUFFALO; ++i )
	{
		const PieceInfo *pInfo = m_pieces[i]->GetPieceInfo();
		if ( pInfo->isAlive && (pInfo->cell.row == RIVER_ROW))
		{
			return m_pieces[i];
		}
	}
	return nullptr;
}

GameContext::GameContext(uint8_t row, uint8_t col) :
	boardRow(row), boardCol(col), turnNumber(0), board(0)
{
	board = new PieceBase**[row];
	for ( uint8_t r = 0; r < row; r++ )
	{
		board[r] = new PieceBase * [col];
		memset(board[r], 0, sizeof(PieceBase *) * col);
	}
	gameState = GameState::Ready;
}

GameContext::~GameContext()
{
	if ( board )
	{
		for ( int r = 0; r < boardRow; ++r )
		{
			delete[] board[r];
		}
	}
	delete[] board;
}

PieceBase* GameContext::GetPiece(const Cell &cell) const
{
	return board[cell.row][cell.col];
}

void GameContext::SetPiece(const Cell &cell, PieceBase *const piece) const
{
	board[cell.row][cell.col] = piece;
}
