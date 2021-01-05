#pragma once
#include <stdexcept>
#include <cstdint>
#include <memory>
#include <vector>
#include <map>
#include <set>


//////////////////////////////////////////////////////////////////////////
// enum class
//////////////////////////////////////////////////////////////////////////

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
* 05. 사냥꾼(Cheif)을 쓰는 사람을 River팀이라고 합니다.
*/

enum Owner : int8_t
{
	Grass = 0,
	River
};

enum PieceType : int8_t
{
	Buffalo = 0,
	Cheif,
	Dog,
};

union PieceID
{
	int32_t key;

	struct
	{
		Owner owner;
	};
	struct
	{
		int8_t __dummy1[1];
		PieceType type;
	};
	struct
	{
		int8_t __dummy2[2];
		int8_t number;
	};

	PieceID(Owner owner, PieceType pieceType, int8_t number)
	{
		this->owner = owner;
		this->type = pieceType;
		this->number = number;
	}

	explicit PieceID(int32_t key = 0)
	{
		this->key = key;
	}
};

inline bool operator<(const PieceID& lhs, const PieceID& rhs)
{
	return lhs.key < rhs.key;
}

//////////////////////////////////////////////////////////////////////////
// struct
//////////////////////////////////////////////////////////////////////////

struct Cell
{
	uint32_t row;
	uint32_t col;
};

