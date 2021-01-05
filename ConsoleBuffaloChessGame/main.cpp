#include <iostream>
#include <Windows.h>

#include "../BuffaloChessGameLib/BuffaloChessGameLib.h"


#ifdef UNICODE

typedef wchar_t xchar;

#else

typedef char xchar;

#endif



void cls(const HANDLE &hOut)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD topLeft = { 0, 0 };

    std::cout.flush();

    if ( !GetConsoleScreenBufferInfo(hOut, &csbi) )
    {
        abort();
    }

    DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

    DWORD written;

    FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

    FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

    SetConsoleCursorPosition(hOut, topLeft);
}

void ChangeChar(const HANDLE &hOut, const xchar &c, const Cell &cell)
{
	COORD here;
	here.X = static_cast<SHORT>( cell.col );
	here.Y = static_cast<SHORT>( cell.row );

	DWORD dw;
	WriteConsoleOutputCharacter(hOut, &c, 1, here, &dw);
}


int main(void)
{
	SetConsoleOutputCP(CP_UTF8);
	system("mode con cols=60 lines=17 | title Buffalo Chess Console"); // 콘솔창 크기 및 제목 설정

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	for ( xchar i = 'a'; i <= 'a'; i++ )
	{
		SetConsoleTextAttribute(hOut, 14);
		for ( int j = 0; j < 1020; j++ )
		{
			printf("%c", i);
		}
	}

	for ( xchar i = 'b'; i <= 'z'; i++ )
	{
		Cell cell;
		cell.col = ( i - 'a' ) % 60;
		cell.row = ( i - 'a' ) / 60;

		ChangeChar(hOut, i, cell);
	}

	SetConsoleTextAttribute(hOut, 9);
	std::cout << "A";
	SetConsoleTextAttribute(hOut, 5);
	std::cout << "B";
	SetConsoleTextAttribute(hOut, 13);
	std::cout << "C";
	
	// SetConsoleTextAttribute(chdr, 14);
	// wprintf(L"%s\n", L"test");
	// SetConsoleTextAttribute(chdr, 2);
	// printf("%s\n", u8"한글");
	// wprintf(L"%s\n", L"\342\230\272");
	// std::cout << "\342\230\272" << std::endl;

	getchar();

	SetConsoleTextAttribute(hOut, 12);
	// IGameHandle *hGame = IGameHandle::CreateGame();
	// std::cout << hGame->GetTurnOwner() << std::endl;
	// 
	// Cell cell = { 0, 0 };
	// hGame->GetHint(cell);


	return 0;
}
