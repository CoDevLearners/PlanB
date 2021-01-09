#include "pch.h"
#include "BuffaloChessGame.h"

#include <iostream>
#include <cassert>

const Cell BuffaloChessGame::Dir[8] = {
		Cell(1, 0), /* u */
		Cell(1, 1), /* ur */
		Cell(0, 1), /* r */
		Cell(-1, 1), /* dr */
		Cell(-1, 0), /* d */
		Cell(-1,-1), /* dl */
		Cell(0,-1), /* l */
		Cell(1,-1), /* ul */
};

void BuffaloChessGame::MakeBoardClean()
{
	for ( int row = 0; row < MAX_BOARD_ROW; ++row )
	{
		for ( int col = 0; col < MAX_BOARD_COL; ++col )
		{
			m_boards[row][col] = InvalidPieceId;
		}
	}
}

void BuffaloChessGame::GenAllGrassPiece()
{
	uint32_t buffaloArrOffset = 0;
	uint32_t boardColOffset = ( MAX_BOARD_COL - NUM_BUFFALO ) / 2;
	uint32_t buffaloRow = MAX_BOARD_ROW - 1;

	for ( uint32_t number = 0; number < NUM_BUFFALO; ++number )
	{
		PieceId id = PieceId(Owner::Grass, PieceType::Buffalo, number);
		Cell cell = Cell(buffaloRow, boardColOffset + number);

		m_boards[cell.row][cell.col] = id;

		uint32_t pieceArrIdx = buffaloArrOffset + id.number;
		m_pieceArr[pieceArrIdx] = Piece(id, cell, true);

		m_alivePiecePtrs.insert(&m_pieceArr[pieceArrIdx]);
	}
}

void BuffaloChessGame::GenAllRiverPiece()
{
	uint32_t dogArrOffset = NUM_BUFFALO;
	uint32_t chiefArrOffset = ( NUM_BUFFALO + NUM_DOG );
	uint32_t boardColOffset = ( MAX_BOARD_COL - ( NUM_DOG + NUM_CHIEF ) ) / 2;
	uint32_t cheifRow = 1;

	uint32_t halfNumDog = NUM_DOG / 2;

	// left side Dog
	for ( uint32_t number = 0; number < halfNumDog; ++number )
	{
		PieceId id = PieceId(Owner::River, PieceType::Dog, number);
		Cell cell = Cell(cheifRow, boardColOffset + number);

		m_boards[cell.row][cell.col] = id;

		uint32_t pieceArrIdx = dogArrOffset + id.number;
		m_pieceArr[pieceArrIdx] = Piece(id, cell, true);

		m_alivePiecePtrs.insert(&m_pieceArr[pieceArrIdx]);
	}

	// Chief
	for ( uint32_t number = 0; number < NUM_CHIEF; ++number )
	{
		PieceId id = PieceId(Owner::River, PieceType::Cheif, number);
		Cell cell = Cell(cheifRow, boardColOffset + halfNumDog + number);

		m_boards[cell.row][cell.col] = id;

		uint32_t pieceArrIdx = chiefArrOffset + id.number;
		m_pieceArr[pieceArrIdx] = Piece(id, cell, true);

		m_alivePiecePtrs.insert(&m_pieceArr[pieceArrIdx]);
	}

	// right side Dog
	for ( uint32_t number = halfNumDog; number < NUM_DOG; ++number )
	{
		PieceId id = PieceId(Owner::River, PieceType::Dog, number);
		Cell cell = Cell(cheifRow, boardColOffset + NUM_CHIEF + number);

		m_boards[cell.row][cell.col] = id;

		uint32_t pieceArrIdx = dogArrOffset + id.number;
		m_pieceArr[pieceArrIdx] = Piece(id, cell, true);

		m_alivePiecePtrs.insert(&m_pieceArr[pieceArrIdx]);
	}
}

bool BuffaloChessGame::InBoard(const Cell &cell)
{
	return ( ( cell.row < MAX_BOARD_ROW ) && ( cell.col < MAX_BOARD_COL ) );
}

BuffaloChessGame::BuffaloChessGame() :
	m_pieceArr(NUM_TOTAL_PIECE),
	m_numSeq(0),
	m_state(GameState::Invalid)
{
	assert(3 < MAX_BOARD_ROW);
	assert(MAX_BOARD_COL >= NUM_BUFFALO);
	assert(MAX_BOARD_COL >= ( NUM_DOG + NUM_CHIEF ));
}

bool BuffaloChessGame::ExistMovableBuffalo(const PieceId &exceptPiece)
{
	uint32_t pieceOffset = 0;

	for ( uint32_t i = pieceOffset; i < NUM_BUFFALO; i++ )
	{
		Piece &buffalo = m_pieceArr[i];
		if ( buffalo.id == exceptPiece )
		{
			continue;
		}

		Cell nextStep = buffalo.cell - Cell(1, 0);
		if ( buffalo.alive && InBoard(nextStep) )
		{
			if ( EmptyCell(nextStep) )
			{
				return true;
			}
		}
	}

	return false;
}

void BuffaloChessGame::CalcBuffaloAction(const Piece &piece, std::vector<Action> &actions)
{
	actions.clear();

	Cell next = piece.cell + Cell(-1, 0);

	if ( !InBoard(next) || !EmptyCell(next) )
	{
		return;
	}

	Action action;
	action.piece = piece;
	action.destination = next;
	if ( next.row == RIVER_ROW )
	{
		action.hasWon = true;
		action.owner = piece.id.owner;
	}

	actions.push_back(action);
}

void BuffaloChessGame::CalcDogAction(const Piece &piece, std::vector<Action> &actions)
{
	actions.clear();

	for ( uint32_t i = 0; i < NumDir; ++i )
	{
		Cell next = piece.cell + Dir[i];
		while ( InBoard(next) && EmptyCell(next) )
		{
			Action action;
			action.piece = piece;
			action.destination = next;
			if ( !ExistMovableBuffalo() )
			{
				action.hasWon = true;
				action.owner = piece.id.owner;
			}

			actions.push_back(action);

			next = next + Dir[i];
		}
	}
}

void BuffaloChessGame::CalcChiefAction(const Piece &piece, std::vector<Action> &actions)
{
	actions.clear();

	for ( uint32_t i = 0; i < NumDir; ++i )
	{
		Cell next = piece.cell + Dir[i];
		if ( InBoard(next) )
		{
			const Piece dstPiece = GetPiece(next);
			if ( dstPiece.id == InvalidPieceId )
			{
				Action action;
				action.piece = piece;
				action.destination = next;
				if ( !ExistMovableBuffalo() )
				{
					action.hasWon = true;
					action.owner = piece.id.owner;
				}

				actions.push_back(action);
			}
			else if ( dstPiece.id.type == PieceType::Buffalo && dstPiece.alive )
			{
				Action action;
				action.piece = piece;
				action.destination = next;
				action.hasKilled = true;
				action.deadPiece = dstPiece;
				if ( !ExistMovableBuffalo(dstPiece.id) )
				{
					action.hasWon = true;
					action.owner = piece.id.owner;
				}

				actions.push_back(action);
			}
		}
	}
}

PieceId BuffaloChessGame::GetPieceId(const Cell &cell)
{
	return m_boards[cell.row][cell.col];
}

void BuffaloChessGame::SetDeadPiece(const PieceId &id)
{
	for ( int i = 0; i < NUM_TOTAL_PIECE; ++i )
	{
		if ( id == m_pieceArr[i].id )
		{
			m_pieceArr[i].alive = false;
			m_alivePiecePtrs.erase(&m_pieceArr[i]);
			m_deadPiecePtrs.insert(&m_pieceArr[i]);
			break;
		}
	}
}

void BuffaloChessGame::SetAlivePieve(const PieceId &id)
{
	for ( int i = 0; i < NUM_TOTAL_PIECE; ++i )
	{
		if ( id == m_pieceArr[i].id )
		{
			m_pieceArr[i].alive = true;
			m_deadPiecePtrs.erase(&m_pieceArr[i]);
			m_alivePiecePtrs.insert(&m_pieceArr[i]);
			break;
		}
	}
}

bool BuffaloChessGame::EmptyCell(const Cell &cell)
{
	return ( InvalidPieceId == GetPieceId(cell) );
}

BuffaloChessGame::~BuffaloChessGame()
{}

bool BuffaloChessGame::Initalize()
{
	if ( m_state == GameState::InGame )
	{
		return false;
	}
	else if ( m_state == GameState::Ready )
	{
		return true;
	}

	m_alivePiecePtrs.clear();
	m_deadPiecePtrs.clear();

	MakeBoardClean();

	GenAllGrassPiece();

	GenAllRiverPiece();

	m_numSeq = 0;
	m_state = GameState::Ready;

	return true;
}

void BuffaloChessGame::MovePiece(const PieceId &id, const Cell &cell)
{
	for ( int i = 0; i < NUM_TOTAL_PIECE; ++i )
	{
		if ( id == m_pieceArr[i].id )
		{
			m_pieceArr[i].cell = cell;
			break;
		}
	}
}

void BuffaloChessGame::Release()
{
	m_state = GameState::Invalid;
}

bool BuffaloChessGame::Update(const Action &action)
{
	if ( action.hasWon )
	{
		if ( action.owner == Owner::Grass )
		{
			m_state = GameState::GameOver;
			return true;
		}
		else if ( action.owner == Owner::River )
		{
			m_state = GameState::GameOver;
			return true;
		}
		return false;
	}

	const Piece &piece = action.piece;
	const Cell &srcCell = piece.cell;
	const Cell &dstCell = action.destination;
	PieceId &refSrcPieceId = m_boards[srcCell.row][srcCell.col];
	PieceId &refDstPieceId = m_boards[dstCell.row][dstCell.col];

	if ( piece.id == InvalidPieceId )
	{
		return false;
	}
	else if ( piece.id != refSrcPieceId )
	{
		return false;
	}
	else if ( action.hasKilled )
	{
		const Piece &deadPiece = action.deadPiece;
		
		if ( refDstPieceId == deadPiece.id )
		{
			refSrcPieceId = InvalidPieceId;
			refDstPieceId = piece.id;
			SetDeadPiece(deadPiece.id);
			MovePiece(piece.id, dstCell);
			++m_numSeq;
			return true;
		}
	}
	else if( refDstPieceId == InvalidPieceId )
	{
		refSrcPieceId = InvalidPieceId;
		refDstPieceId = piece.id;
		MovePiece(piece.id, dstCell);
		++m_numSeq;
		return true;
	}

	return false;
}

Piece BuffaloChessGame::GetPiece(const Cell &cell)
{
	return GetPiece(GetPieceId(cell));
}

bool BuffaloChessGame::BuffaloHasArrived()
{
	uint32_t pieceOffset = 0;

	for ( uint32_t i = pieceOffset; i < NUM_BUFFALO; i++ )
	{
		Piece &buffalo = m_pieceArr[i];
		if ( buffalo.alive && ( buffalo.cell.row == RIVER_ROW ) )
		{
			return true;
		}
	}

	return false;
}

Piece BuffaloChessGame::GetPiece(const PieceId &pieceId)
{
	if ( pieceId == InvalidPieceId )
	{
		return Piece();
	}

	for ( int i = 0; i < NUM_TOTAL_PIECE; i++ )
	{
		const Piece &piece = m_pieceArr[i];
		if ( piece.id == pieceId )
		{
			return piece;
		}
	}

	return Piece();
}

std::vector<Action> BuffaloChessGame::GetActions(const Owner &owner, const Cell &cell)
{
	std::vector<Action> actions;
	const Piece piece = GetPiece(cell);
	if ( owner != piece.id.owner )
	{
		return actions;
	}

	switch ( piece.id.type )
	{
	case PieceType::Buffalo:
		CalcBuffaloAction(piece, actions);
		break;

	case PieceType::Dog:
		CalcDogAction(piece, actions);
		break;

	case PieceType::Cheif:
		CalcChiefAction(piece, actions);
		break;
	default:
		break;
	}

	return actions;
}

Owner BuffaloChessGame::GetTurnOwner()
{
	return Owner(m_numSeq % 2);
}

std::vector<Piece> BuffaloChessGame::GetAllPieces()
{
	return m_pieceArr;
}

std::vector<Piece> BuffaloChessGame::GetAlivePieces()
{
	size_t numAlivePiece = m_alivePiecePtrs.size();
	std::vector<Piece> result(numAlivePiece);

	size_t pieceIdx = 0;
	for ( auto it : m_alivePiecePtrs )
	{
		result[pieceIdx++] = *it;
	}

	return result;
}

std::vector<Piece> BuffaloChessGame::GetDeadPieces()
{
	size_t numAlivePiece = m_deadPiecePtrs.size();
	std::vector<Piece> result(numAlivePiece);

	size_t pieceIdx = 0;
	for ( auto it : m_deadPiecePtrs )
	{
		result[pieceIdx++] = *it;
	}

	return result;
}

bool BuffaloChessGame::IsOver()
{
	return ( m_state == GameState::GameOver );
}

