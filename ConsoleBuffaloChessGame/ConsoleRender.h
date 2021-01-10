#pragma once

#include <iostream>
#include <Windows.h>
#include "../BuffaloChessGameLib/Common.h"

#ifdef UNICODE

typedef wchar_t xchar;

#else

typedef char xchar;

#endif

class ConsoleRender {
private:
	enum StyleType {
		Default = 0,
		Buffalo,
		Dog,
		Chief,
		River,
		Grass,
		Hint,
	};

private:
	HANDLE m_hOut;

	const char *ConsoleTitle = u8"Buffalo Chess Console";
	const short ConsoleCol = 58;
	const short ConsoleRow = 40;
	const short ChessAreaHeight = 22;

	const char* BuffaloObj = u8"¼Ò";
	const char* ChiefObj   = u8"ÃÑ";
	const char* DogObj	   = u8"°³";
	const char* RiverObj   = u8"¹°";
	const char* HintObj	   = u8"¡Û";
	const char* PrevPosObj = u8"¢Á";
	const xchar BlankObj   = TEXT(' ');

	void LoadStyle(StyleType type = StyleType::Default);
	void Print(short x, short y, const char *u8str);

	void Init();

public:
	enum class State {
		WaitSelect,
		WaitInput,
	};

	ConsoleRender();

	void PrintChessBoard();

	void PrintTurnHelp(const PlayerType &owner);
	void PrintStateHelp(const State &state);

	void PrintPiece(const PieceInfo &piece);
	void ClearInputArea();
	void PrintHint(const Action &action);

	void PrintVictory(const PlayerType &owner);
};

