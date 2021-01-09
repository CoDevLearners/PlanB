#include "ConsoleRender.h"

#include <iostream>



void ConsoleRender::Init()
{
	SetConsoleOutputCP(CP_UTF8);
	system("mode con cols=58 lines=40 | title Buffalo Chess Console"); // 콘솔창 크기 및 제목 설정

	m_hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if ( !GetConsoleScreenBufferInfo(m_hOut, &m_csbi) )
	{
		exit(3);
	}

	SetConsoleTextAttribute(m_hOut, 8);
	SetConsoleCursorPosition(m_hOut, { 0, 0 });

	DWORD written;
	DWORD length = m_csbi.dwSize.X * m_csbi.dwSize.Y;
	FillConsoleOutputCharacter(m_hOut, TEXT(' '), length, { 0, 0 }, &written);

	for ( short i = 0; i < 57; ++i )
	{
		SetConsoleCursorPosition(m_hOut, { i, 0 });
		std::cout << u8"※";
		SetConsoleCursorPosition(m_hOut, { i, 22 });
		std::cout << u8"※";
	}
	
	for ( short i = 1; i < 22; ++i )
	{
		SetConsoleCursorPosition(m_hOut, { 0,  i }); std::cout << u8"§";
		SetConsoleCursorPosition(m_hOut, { 56, i }); std::cout << u8"§";
	}

	std::cout.flush();
}

void ConsoleRender::ClearInputArea()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	short areaRow = 26;
	COORD topLeft = { 0, areaRow };

	std::cout.flush();

	if ( !GetConsoleScreenBufferInfo(m_hOut, &csbi) )
	{
		exit(3);
	}

	DWORD length = csbi.dwSize.X * ( csbi.dwSize.Y - areaRow );

	DWORD written;

	FillConsoleOutputCharacter(m_hOut, TEXT(' '), length, topLeft, &written);

	FillConsoleOutputAttribute(m_hOut, csbi.wAttributes, length, topLeft, &written);

	SetConsoleCursorPosition(m_hOut, topLeft);
}

void ConsoleRender::PrintHint(const IHint &action)
{
	//std::cout.flush();
	//
	//short xOffset = 5;
	//short yOffset = 3;
	//short yStep = 2;
	//short xStep = 4;
	//
	//if ( action.hasKilled )
	//{
	//	const Piece &deadPiece = action.deadPiece;
	//	const Cell &deadCell = deadPiece.cell;
	//
	//	COORD pos = {
	//			xOffset + 3 + ( deadCell.col * xStep ),
	//			yOffset + 2 + ( ( MAX_BOARD_ROW - 1 - deadCell.row ) * yStep )
	//	};
	//	SetConsoleTextAttribute(m_hOut, 4);
	//	SetConsoleCursorPosition(m_hOut, pos);
	//	std::cout << u8"소";
	//}
	//else
	//{
	//	const Cell &cell = action.destination;
	//	COORD pos = {
	//		xOffset + 3 + ( cell.col * xStep ),
	//		yOffset + 2 + ( ( MAX_BOARD_ROW - 1 - cell.row ) * yStep )
	//	};
	//	SetConsoleTextAttribute(m_hOut, 8);
	//	SetConsoleCursorPosition(m_hOut, pos);
	//	std::cout << u8"○";
	//}
}

void ConsoleRender::PrintVictory(const PlayerType &owner)
{
	ClearInputArea();

	std::cout.flush();
	DWORD written;
	FillConsoleOutputCharacter(m_hOut, TEXT(' '), 57, { 0, 24 }, &written);

	if ( owner == PlayerType::Grass )
	{
		SetConsoleCursorPosition(m_hOut, { 0, 24 });

		SetConsoleTextAttribute(m_hOut, 10);
		std::cout << u8"Grass";
		SetConsoleTextAttribute(m_hOut, 15);
		std::cout << u8" 팀이 이겼습니다";
	}
	else if ( owner == PlayerType::River )
	{
		SetConsoleCursorPosition(m_hOut, { 0, 24 });

		SetConsoleTextAttribute(m_hOut, 12);
		std::cout << u8"River";
		SetConsoleTextAttribute(m_hOut, 15);
		std::cout << u8" 팀이 이겼습니다.";
	}
}

void ConsoleRender::ChangeChar(const HANDLE &hOut, const xchar &c, const short &x, const short &y)
{
	std::cout.flush();

	COORD here;
	here.X = x;
	here.Y = y;
	DWORD dw;
	WriteConsoleOutputCharacter(hOut, &c, 1, here, &dw);
}

ConsoleRender::ConsoleRender() :
	m_hOut(0)
{
	Init();
}

void ConsoleRender::PrintChessBoard()
{
	short xOffset = 5;
	short yOffset = 3;
	SetConsoleTextAttribute(m_hOut, 15);
	SetConsoleCursorPosition(m_hOut, { xOffset + 1, yOffset + 0 });
	std::cout << u8"│ １│ ２│ ３│ ４│ ５│ ６│ ７│ ８│ ９│ 10│ 11│ ";
	SetConsoleCursorPosition(m_hOut, { xOffset + 0, yOffset + 1 });
	std::cout << u8"─┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼─";
	SetConsoleCursorPosition(m_hOut, { xOffset + 0, yOffset + 2 });
	std::cout << u8"7│   │   │   │   │   │   │   │   │   │   │   │ 7";
	SetConsoleCursorPosition(m_hOut, { xOffset + 0, yOffset + 3 });
	std::cout << u8"─┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼─";
	SetConsoleCursorPosition(m_hOut, { xOffset + 0, yOffset + 4 });
	std::cout << u8"6│   │   │   │   │   │   │   │   │   │   │   │ 6";
	SetConsoleCursorPosition(m_hOut, { xOffset + 0, yOffset + 5 });
	std::cout << u8"─┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼─";
	SetConsoleCursorPosition(m_hOut, { xOffset + 0, yOffset + 6 });
	std::cout << u8"5│   │   │   │   │   │   │   │   │   │   │   │ 5";
	SetConsoleCursorPosition(m_hOut, { xOffset + 0, yOffset + 7 });
	std::cout << u8"─┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼─";
	SetConsoleCursorPosition(m_hOut, { xOffset + 0, yOffset + 8 });
	std::cout << u8"4│   │   │   │   │   │   │   │   │   │   │   │ 4";
	SetConsoleCursorPosition(m_hOut, { xOffset + 0, yOffset + 9 });
	std::cout << u8"─┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼─";
	SetConsoleCursorPosition(m_hOut, { xOffset + 0, yOffset + 10 });
	std::cout << u8"3│   │   │   │   │   │   │   │   │   │   │   │ 3";
	SetConsoleCursorPosition(m_hOut, { xOffset + 0, yOffset + 11 });
	std::cout << u8"─┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼─";
	SetConsoleCursorPosition(m_hOut, { xOffset + 0, yOffset + 12 });
	std::cout << u8"2│   │   │   │   │   │   │   │   │   │   │   │ 2";
	SetConsoleCursorPosition(m_hOut, { xOffset + 0, yOffset + 13 });
	std::cout << u8"─┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼─";
	SetConsoleCursorPosition(m_hOut, { xOffset + 0, yOffset + 14 });
	std::cout << u8"1│   │   │   │   │   │   │   │   │   │   │   │ 1";
	SetConsoleCursorPosition(m_hOut, { xOffset + 0, yOffset + 15 });
	std::cout << u8"─┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼─";
	SetConsoleCursorPosition(m_hOut, { xOffset + 1, yOffset + 16 });
	std::cout << u8"│ １│ ２│ ３│ ４│ ５│ ６│ ７│ ８│ ９│ 10│ 11│ ";

	SetConsoleTextAttribute(m_hOut, 9);
	for ( short i = 0; i < 11; ++i )
	{
		SetConsoleCursorPosition(m_hOut, { xOffset + 3 + ( 4 * i ), yOffset + 14 });
		std::cout << u8"물";
	}

}

void ConsoleRender::PrintPiece(const PieceInfo &piece)
{
	// std::cout.flush();
	// 
	// short xOffset = 5;
	// short yOffset = 3;
	// short yStep   = 2;
	// short xStep   = 4;
	// 
	// if ( piece.id.type == PieceType::Buffalo )
	// {
	// 	SetConsoleTextAttribute(m_hOut, 6);
	// 
	// 	const Cell &cell = piece.cell;
	// 	COORD pos = { 
	// 		xOffset + 3 + ( cell.col * xStep ),
	// 		yOffset + 2 + ( ( MAX_BOARD_ROW - 1 - cell.row ) * yStep ) 
	// 	};
	// 	SetConsoleCursorPosition(m_hOut, pos);
	// 
	// 	std::cout << u8"소";
	// }
	// else if ( piece.id.type == PieceType::Dog )
	// {
	// 	SetConsoleTextAttribute(m_hOut, 7);
	// 
	// 	const Cell &cell = piece.cell;
	// 	COORD pos = { 
	// 		xOffset + 3 + ( cell.col * xStep ),
	// 		yOffset + 2 + ( ( MAX_BOARD_ROW - 1 - cell.row ) * yStep ) 
	// 	};
	// 	SetConsoleCursorPosition(m_hOut, pos);
	// 
	// 	std::cout << u8"개";
	// }
	// else if ( piece.id.type == PieceType::Cheif )
	// {
	// 	SetConsoleTextAttribute(m_hOut, 4);
	// 
	// 	const Cell &cell = piece.cell;
	// 	COORD pos = { 
	// 		xOffset + 3 + ( cell.col * xStep ),
	// 		yOffset + 2 + ( ( MAX_BOARD_ROW - 1 - cell.row ) * yStep ) 
	// 	};
	// 	SetConsoleCursorPosition(m_hOut, pos);
	// 
	// 	std::cout << u8"총";
	// }
}

void ConsoleRender::PrintTurnHelp(const PlayerType &owner)
{
	// std::cout.flush();
	// DWORD written;
	// FillConsoleOutputCharacter(m_hOut, TEXT(' '), 57, { 0, 24 }, &written);
	// 
	// if ( owner == Owner::Grass )
	// {
	// 	SetConsoleCursorPosition(m_hOut, { 0, 24 });
	// 
	// 	SetConsoleTextAttribute(m_hOut, 10);
	// 	std::cout << u8"Grass";
	// 	SetConsoleTextAttribute(m_hOut, 15);
	// 	std::cout << u8" 팀 차례입니다.";
	// }
	// else if ( owner == Owner::River )
	// {
	// 	SetConsoleCursorPosition(m_hOut, { 0, 24 });
	// 
	// 	SetConsoleTextAttribute(m_hOut, 12);
	// 	std::cout << u8"River";
	// 	SetConsoleTextAttribute(m_hOut, 15);
	// 	std::cout << u8" 팀 차례입니다.";
	// }
}

void ConsoleRender::PrintStateHelp(const State &state)
{
	std::cout.flush();
	SetConsoleTextAttribute(m_hOut, 15);

	if ( state == State::WaitInput )
	{
		SetConsoleCursorPosition(m_hOut, { 1, 26 });
		std::cout << u8"기물 좌표를 입력하세요";
		SetConsoleCursorPosition(m_hOut, { 2, 27 });
	}
	else if ( state == State::WaitSelect )
	{
		SetConsoleCursorPosition(m_hOut, { 1, 28 });
		std::cout << u8"목적지 좌표를 입력하세요";
		SetConsoleCursorPosition(m_hOut, { 2, 29 });
	}
}
