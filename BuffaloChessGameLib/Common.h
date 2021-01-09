#pragma once

#include <ostream>
#include <cstdint>

/**
* 7행, 11열
*
* 🐮🐮🐮🐮🐮🐮🐮🐮🐮🐮🐮 Grass 팀
* 🔲🔲🔲🔲🔲🔲🔲🔲🔲🔲🔲
* 🔲🔲🔲🔲🔲🔲🔲🔲🔲🔲🔲
* 🔲🔲🔲🔲🔲🔲🔲🔲🔲🔲🔲
* 🔲🔲🔲🔲🔲🔲🔲🔲🔲🔲🔲
* 🔲🔲🔲🐶🐶🧔🐶🐶🔲🔲🔲
* 🔳🔳🔳🔳🔳🔳🔳🔳🔳🔳🔳 River 팀
*
* 01. 좌하단을 (0, 0) 으로 본다.
* 02. 넘버링은 좌측 기준으로 1번부터 부여한다.
* 03. 한 칸을 Cell(셀) 이라고 부른다.
* 04. 버팔로(Buffalo)를 쓰는 사람을 Grass팀이라고 합니다.
* 05. 사냥꾼(Chief)을 쓰는 사람을 River팀이라고 합니다.
*/


using PieceId = uint8_t;

enum class GameState {
	Ready = 0,
	InGame,
	GameOver,
};

enum class PlayerType {
	None = 0,
	Grass,
	River,
};

enum class PieceType {
	None = 0,
	Buffalo,
	Dog,
	Chief
};

struct Cell {
	uint32_t row;
	uint32_t col;

	Cell();
	Cell(uint32_t row, uint32_t col);
};

Cell operator+(const Cell &lhs, const Cell &rhs);
Cell operator-(const Cell &lhs, const Cell &rhs);
bool operator==(const Cell &lhs, const Cell &rhs);


struct PieceInfo {
	PlayerType owner;
	PieceType  type;
	PieceId	   id;
	bool	   isAlive;
	Cell	   cell;

	PieceInfo();
	PieceInfo(PlayerType owner, PieceType type, PieceId id, bool isAlive, Cell cell);
};

bool operator==(const PieceInfo &lhs, const PieceInfo &rhs);

struct Action {
	PieceInfo piece;
	Cell destination;

	bool hasKill;
	PieceInfo deadPiece;

	bool hasWon;
	PlayerType player;

	Action();
};
