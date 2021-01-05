#include "pch.h"
#include "BuffaloChessGame.h"

#include <iostream>

BuffaloChessGame::BuffaloChessGame() :
	m_numSeq(0),
	m_state(GameState::Invalid),
	m_numAlivePieces(0),
	m_numDeadPieces(0)
{}

BuffaloChessGame::~BuffaloChessGame()
{}

bool BuffaloChessGame::Initalize()
{
	if ( m_state == GameState::InGame )
	{
		return false;
	}

	uint32_t grassRow = MAX_BOARD_ROW - 1;
	// Buffalo 기물 초기화
	for ( uint32_t col = 0; col < NUM_BUFFALO; ++col )
	{
		m_boards[grassRow][col] = PieceId(Owner::Grass, PieceType::Buffalo, col);
	}

	// 빈 칸 초기화
	for ( uint32_t row = 0; row < grassRow; ++row )
	{
		for ( uint32_t col = 0; col < MAX_BOARD_COL; ++col )
		{
			m_boards[row][col] = IvalidPieceId;
		}
	}

	uint32_t centerCol = MAX_BOARD_COL / 2;
	uint32_t cheifRow = 1;

	// Cheif 기물 초기화
	m_boards[cheifRow][centerCol] = PieceId(Owner::River, PieceType::Cheif, 0);

	// Dog 기물 초기화
	for ( uint32_t col = 0; col < NUM_DOG; ++col )
	{
		if ( col / 2 )
		{
			m_boards[cheifRow][centerCol - 1 + col] = PieceId(Owner::River, PieceType::Dog, col);
		}
		else
		{
			m_boards[cheifRow][centerCol - 2 + col] = PieceId(Owner::River, PieceType::Dog, col);
		}
	}

	m_numSeq = 0;
	m_state = GameState::InGame;

	return true;

	return false;
}

void BuffaloChessGame::Release()
{}

bool BuffaloChessGame::Update(const Action &action)
{
	return false;
}

Piece BuffaloChessGame::GetPiece(const Cell &cell)
{
	return Piece();
}

Piece BuffaloChessGame::GetPiece(const PieceId &pieceId)
{
	return Piece();
}

std::vector<Action> BuffaloChessGame::GetActions(const Cell &cell)
{
	return std::vector<Action>();
}

Owner BuffaloChessGame::GetTurnOwner()
{
	return Owner();
}

std::vector<Piece> BuffaloChessGame::GetAllPieces()
{
	return std::vector<Piece>();
}

std::vector<Piece> BuffaloChessGame::GetAlivePieces()
{
	return std::vector<Piece>();
}

std::vector<Piece> BuffaloChessGame::GetDeadPieces()
{
	return std::vector<Piece>();
}

