#pragma once

#include <Windows.h>
#include "../BuffaloChessGameLib/Common.h"

#ifdef UNICODE

typedef wchar_t xchar;

#else

typedef char xchar;

#endif

class ConsoleRender {
private:
	HANDLE m_hOut;
	CONSOLE_SCREEN_BUFFER_INFO m_csbi;

	void Init();
	void ChangeChar(const HANDLE &hOut, const xchar &c, const short &x, const short &y);

public:
	enum class State {
		WaitSelect,
		WaitInput,
	};



	ConsoleRender();

	void PrintChessBoard();
	void PrintTurnHelp(const Owner &owner);
	void PrintStateHelp(const State &state);

	void PrintPiece(const Piece &piece);
	void ClearInputArea();
	void PrintHint(const Action &action);

	void PrintVictory(const Owner &owner);
};

