﻿#pragma once

#include <ostream>
#include <cstdint>

#define MAX_BOARD_ROW 7
#define MAX_BOARD_COL 11
#define NUM_BUFFALO   (11)
#define NUM_DOG		  (4)
#define NUM_CHIEF	  (1)
#define RIVER_ROW	  (0)

#define __VAR_TO_STR(v)	#v

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


// Grass(버팔로), River(사냥꾼)
enum class Owner : uint8_t {
	Invalid = 0xff,
	Grass = 0x00,
	River,
};

// 기물 종류 
//   Grass 팀
//     Buffalo
//   River 팀
//     Chief, Dog
enum class PieceType : uint8_t {
	Invalid = 0xff,
	Buffalo = 0x00,
	Cheif,
	Dog,
};

union PieceId {
private:
	uint32_t key;

public:
	struct {
		Owner owner;
	};
	struct {
		uint8_t __dummy1;
		PieceType type;
	};
	struct {
		uint16_t __dummy2;
		uint16_t number;
	};

	operator uint32_t () const;

	// 기본 생성 시 Invalid ID
	//   Invalid ID = owner(Ownwer::Invalid), pieceType(PieceType::Invalid), number(-1)
	PieceId();

	PieceId(Owner owner, PieceType pieceType, uint16_t number);
};

const PieceId InvalidPieceId = PieceId();

struct Cell {
	uint32_t row;
	uint32_t col;

	Cell();
	Cell(uint32_t row, uint32_t col);
};

Cell operator+(const Cell &lhs, const Cell &rhs);
Cell operator-(const Cell &lhs, const Cell &rhs);
bool operator==(const Cell &lhs, const Cell &rhs);


struct Piece
{
	PieceId id; // 고정
	Cell    cell;
	bool    alive;

	Piece();
	Piece(PieceId id, Cell cell, bool alive);
};

struct Action
{
	// 누군가의 행동
	Piece piece; // 여기의 얘가
	Cell destination; // 여기로

	// 누군가의 죽음
	bool hasKilled;
	Piece deadPiece;
	
	// 누군가의 승리
	bool hasWon;
	Owner owner;

	Action();
};