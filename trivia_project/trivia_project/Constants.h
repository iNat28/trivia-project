
#pragma once
#include "pch.h"

enum class Codes
{
	ERROR_CODE,

	//Login
	LOGIN = 10,
	SIGNUP,
	LOGOUT,

	//Room
	GET_ROOM = 20,
	GET_PLAYERS_IN_ROOM,
	JOIN_ROOM,
	CREATE_ROOM,

	//Statistics
	HIGH_SCORE = 30
};

typedef char Byte;
typedef std::vector<Byte> Buffer;

#define MSG_CODE_SIZE sizeof(Byte)
#define MSG_LEN_SIZE 4 * sizeof(Byte)