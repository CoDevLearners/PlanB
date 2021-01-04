#include "pch.h"
#include "BuffaloChessGame.h"

#include <iostream>

BuffaloChessGame::BuffaloChessGame() :
	m_numSeq(0),
	m_state(GameState::Invalid)
{}

BuffaloChessGame::~BuffaloChessGame()
{}

bool BuffaloChessGame::Initalize()
{
	if ( m_state == GameState::InGame )
	{
		return false;
	}

	uint32_t grassRow   = MAX_BOARD_ROW - 1;
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
    uint32_t cheifRow  = 1;

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
}

void BuffaloChessGame::Release()
{
	m_state = GameState::Invalid;
}

bool BuffaloChessGame::Update(IAction *pAction, UpdateHandler hUpdate)
{
	throw std::logic_error("Update NotImpletment\n");
    return false;
}

std::vector<Cell> BuffaloChessGame::GetHint(const Cell &cell)
{
	std::vector<Cell> rtv;

	if ( cell.row >= MAX_BOARD_ROW || cell.col >= MAX_BOARD_COL )
	{
		return rtv;
	}

	throw std::logic_error("GetHint NotImpletment\n");


	m_boards[cell.row][cell.col];


    return std::vector<Cell>();
}

Owner BuffaloChessGame::GetTurnOwner()
{
	return Owner(m_numSeq % 2);
}
