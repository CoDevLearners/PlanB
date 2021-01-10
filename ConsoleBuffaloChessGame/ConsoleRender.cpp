#include "ConsoleRender.h"


void ConsoleRender::LoadStyle(StyleType type)
{
	switch ( type )
	{
	case ConsoleRender::Hint:
		SetConsoleTextAttribute(m_hOut, 14);
		break;
	case ConsoleRender::Buffalo:
		SetConsoleTextAttribute(m_hOut, 2);
		break;
	case ConsoleRender::Dog:
		SetConsoleTextAttribute(m_hOut, 7);
		break;
	case ConsoleRender::Chief:
		SetConsoleTextAttribute(m_hOut, 4);
		break;
	case ConsoleRender::River:
		SetConsoleTextAttribute(m_hOut, 9);
		break;
	case ConsoleRender::Grass:
		SetConsoleTextAttribute(m_hOut, 2);
		break;
	default:
		SetConsoleTextAttribute(m_hOut, 15);
		break;
	}
}

void ConsoleRender::Print(short x, short y, const char *u8str)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(m_hOut, pos);
	printf("%s", u8str);
	fflush(stdout);
}

void ConsoleRender::Init()
{
	m_hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleOutputCP(CP_UTF8);
	char buf[256] = { 0 }; // "mode con cols=%d lines=%d | title %s";
	sprintf(buf, "mode con cols=%d lines=%d | title %s", ConsoleCol, ConsoleRow, ConsoleTitle);
	system(buf); // 콘솔창 크기 및 제목 설정

	LoadStyle(StyleType::Default);
	SetConsoleCursorPosition(m_hOut, { 0, 0 });

	DWORD written;
	DWORD length = ConsoleCol * ConsoleRow;
	
	FillConsoleOutputCharacter(m_hOut, BlankObj, length, { 0, 0 }, &written);

	for ( short i = 0; i < ConsoleCol -1; ++i )
	{
		Print(i, 0, u8"※");
		Print(i, ChessAreaHeight, u8"※");
	}
	
	for ( short i = 1; i < ChessAreaHeight; ++i )
	{
		Print(0, i, u8"§");
		Print(ConsoleCol - 2, i, u8"§");
	}
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

void ConsoleRender::PrintHint(const Action &action)
{
	short xOffset = 5;
	short yOffset = 3;
	short yStep = 2;
	short xStep = 4;
	short boardRow = 7;
	
	if ( action.hasKilled )
	{
		const PieceInfo &deadPiece = action.deadPiece;
		const Cell &deadCell = deadPiece.cell;
	
		LoadStyle(StyleType::Hint);
		Print(
			xOffset + 3 + ( deadCell.col * xStep ), 
			yOffset + 2 + ( ( boardRow - 1 - deadCell.row ) * yStep ), 
			BuffaloObj);
	}
	else
	{
		const Cell &cell = action.destination;

		LoadStyle(StyleType::Hint);
		if ( cell.row != 0 )
		{
			Print(
				xOffset + 3 + ( cell.col * xStep ),
				yOffset + 2 + ( ( boardRow - 1 - cell.row ) * yStep ),
				HintObj);
		}
		else
		{
			Print(
				xOffset + 3 + ( cell.col * xStep ),
				yOffset + 2 + ( ( boardRow - 1 - cell.row ) * yStep ),
				RiverObj);
		}
	}
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

ConsoleRender::ConsoleRender() :
	m_hOut(0)
{
	Init();
}

void ConsoleRender::PrintChessBoard()
{
	short xOffset = 5;
	short yOffset = 3;
	LoadStyle(StyleType::Default);

	Print(xOffset + 1, yOffset +  0, u8"│ １│ ２│ ３│ ４│ ５│ ６│ ７│ ８│ ９│ 10│ 11│ ");
	Print(xOffset + 0, yOffset +  1, u8"─┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼──");
	Print(xOffset + 0, yOffset +  2, u8"7│   │   │   │   │   │   │   │   │   │   │   │ 7");
	Print(xOffset + 0, yOffset +  3, u8"─┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼──");
	Print(xOffset + 0, yOffset +  4, u8"6│   │   │   │   │   │   │   │   │   │   │   │ 6");
	Print(xOffset + 0, yOffset +  5, u8"─┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼──");
	Print(xOffset + 0, yOffset +  6, u8"5│   │   │   │   │   │   │   │   │   │   │   │ 5");
	Print(xOffset + 0, yOffset +  7, u8"─┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼──");
	Print(xOffset + 0, yOffset +  8, u8"4│   │   │   │   │   │   │   │   │   │   │   │ 4");
	Print(xOffset + 0, yOffset +  9, u8"─┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼──");
	Print(xOffset + 0, yOffset + 10, u8"3│   │   │   │   │   │   │   │   │   │   │   │ 3");
	Print(xOffset + 0, yOffset + 11, u8"─┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼──");
	Print(xOffset + 0, yOffset + 12, u8"2│   │   │   │   │   │   │   │   │   │   │   │ 2");
	Print(xOffset + 0, yOffset + 13, u8"─┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼──");
	Print(xOffset + 0, yOffset + 14, u8"1│   │   │   │   │   │   │   │   │   │   │   │ 1");
	Print(xOffset + 0, yOffset + 15, u8"─┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼──");
	Print(xOffset + 1, yOffset + 16, u8"│ １│ ２│ ３│ ４│ ５│ ６│ ７│ ８│ ９│ 10│ 11│ ");

	LoadStyle(StyleType::River);
	for ( short i = 0; i < 11; ++i )
	{
		Print(xOffset + 3 + ( 4 * i ), yOffset + 14, RiverObj);
	}

}

void ConsoleRender::PrintPiece(const PieceInfo &piece)
{
	std::cout.flush();
	
	short xOffset = 5;
	short yOffset = 3;
	short yStep   = 2;
	short xStep   = 4;
	short boardRow = 7;
	
	const Cell &cell = piece.cell;

	if ( piece.type == PieceType::Buffalo )
	{
		LoadStyle(StyleType::Buffalo);
		Print(
			xOffset + 3 + ( cell.col * xStep ),
			yOffset + 2 + ( ( boardRow - 1 - cell.row ) * yStep ),
			BuffaloObj
		);
	}
	else if ( piece.type == PieceType::Dog )
	{
		LoadStyle(StyleType::Dog);
		Print(
			xOffset + 3 + ( cell.col * xStep ),
			yOffset + 2 + ( ( boardRow - 1 - cell.row ) * yStep ),
			DogObj
		);
	}
	else if ( piece.type == PieceType::Chief )
	{
		LoadStyle(StyleType::Chief);
		Print(
			xOffset + 3 + ( cell.col * xStep ),
			yOffset + 2 + ( ( boardRow - 1 - cell.row ) * yStep ),
			ChiefObj
		);
	}
}

void ConsoleRender::PrintTurnHelp(const PlayerType &owner)
{
	DWORD written;
	FillConsoleOutputCharacter(m_hOut, TEXT(' '), 57, { 0, 24 }, &written);
	
	if ( owner == PlayerType::Grass )
	{
		LoadStyle(StyleType::Grass);
		Print(0, 24, u8"Grass");
		LoadStyle(StyleType::Default);
		Print(5, 24, u8" 팀 차례입니다.");
	}
	else if ( owner == PlayerType::River )
	{
		LoadStyle(StyleType::River);
		Print(0, 24, u8"River");
		LoadStyle(StyleType::Default);
		Print(5, 24, u8" 팀 차례입니다.");
	}
}

void ConsoleRender::PrintStateHelp(const State &state)
{
	if ( state == State::WaitInput )
	{
		LoadStyle(StyleType::Default);
		Print(1, 26, u8"기물 좌표를 입력하세요");
		SetConsoleCursorPosition(m_hOut, { 2, 27 });
	}
	else if ( state == State::WaitSelect )
	{
		LoadStyle(StyleType::Default);
		Print(1, 28, u8"목적지 좌표를 입력하세요");
		SetConsoleCursorPosition(m_hOut, { 2, 29 });
	}
}
