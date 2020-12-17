#include "BuffaloChessGame.h"

#include "Cheif.h"
#include "Dog.h"
#include "Buffalo.h"

bool BuffaloChessGame::Initalize()
{
	if (!InitPieces())
	{
		return false;
	}

	if (!InitBoard())
	{
		return false;
	}

	return true;
}

const std::vector<Actions> BuffaloChessGame::GetActions(PieceID pieceID)
{
	return std::vector<Actions>();
}

bool BuffaloChessGame::Update(const Actions& moving)
{
	return false;
}

bool BuffaloChessGame::InitPieces()
{
	/**
	 * 7행, 11열
	 * 
	 * 🐮🐮🐮🐮🐮🐮🐮🐮🐮🐮🐮
	 * 🔲🔲🔲🔲🔲🔲🔲🔲🔲🔲🔲
	 * 🔲🔲🔲🔲🔲🔲🔲🔲🔲🔲🔲
	 * 🔲🔲🔲🔲🔲🔲🔲🔲🔲🔲🔲
	 * 🔲🔲🔲🔲🔲🔲🔲🔲🔲🔲🔲
	 * 🔲🔲🔲🐶🐶🧔🐶🐶🔲🔲🔲
	 * 🔳🔳🔳🔳🔳🔳🔳🔳🔳🔳🔳
	 * 
	 * 좌하단을 (0, 0) 으로 본다.
	 * 넘버링은 좌측 기준으로 1번부터 부여한다.
	 */

	try
	{
	/*	m_pieces[PieceID()] =  .emplace(PieceName::Cheif, std::shared_ptr<PieceBase>(new Cheif{ Cell{ 1, 5 } }));

		m_pieces.emplace(PieceName::Dog_01, std::shared_ptr<PieceBase>(new Dog{ Cell{ 1, 3 } }));
		m_pieces.emplace(PieceName::Dog_02, std::shared_ptr<PieceBase>(new Dog{ Cell{ 1, 4 } }));
		m_pieces.emplace(PieceName::Dog_03, std::shared_ptr<PieceBase>(new Dog{ Cell{ 1, 6 } }));
		m_pieces.emplace(PieceName::Dog_04, std::shared_ptr<PieceBase>(new Dog{ Cell{ 1, 7 } }));

		m_pieces.emplace(PieceName::BuffaLo_01, std::shared_ptr<PieceBase>(new Buffalo{ Cell{ 6, 0 } }));
		m_pieces.emplace(PieceName::BuffaLo_02, std::shared_ptr<PieceBase>(new Buffalo{ Cell{ 6, 1 } }));
		m_pieces.emplace(PieceName::BuffaLo_03, std::shared_ptr<PieceBase>(new Buffalo{ Cell{ 6, 2 } }));
		m_pieces.emplace(PieceName::BuffaLo_04, std::shared_ptr<PieceBase>(new Buffalo{ Cell{ 6, 3 } }));
		m_pieces.emplace(PieceName::BuffaLo_05, std::shared_ptr<PieceBase>(new Buffalo{ Cell{ 6, 4 } }));
		m_pieces.emplace(PieceName::BuffaLo_06, std::shared_ptr<PieceBase>(new Buffalo{ Cell{ 6, 5 } }));
		m_pieces.emplace(PieceName::BuffaLo_07, std::shared_ptr<PieceBase>(new Buffalo{ Cell{ 6, 6 } }));
		m_pieces.emplace(PieceName::BuffaLo_08, std::shared_ptr<PieceBase>(new Buffalo{ Cell{ 6, 7 } }));
		m_pieces.emplace(PieceName::BuffaLo_09, std::shared_ptr<PieceBase>(new Buffalo{ Cell{ 6, 8 } }));
		m_pieces.emplace(PieceName::BuffaLo_10, std::shared_ptr<PieceBase>(new Buffalo{ Cell{ 6, 9 } }));
		m_pieces.emplace(PieceName::BuffaLo_11, std::shared_ptr<PieceBase>(new Buffalo{ Cell{ 6, 10 } }));*/
	}
	catch (const std::exception&)
	{
		return false;
	}

	return true;
}

bool BuffaloChessGame::InitBoard()
{
	//for (auto&[key, value] : m_pieces)
	//{
	//	m_board.SetPiece(value->GetPosition(), value->)-
	//}

	return false;
}
