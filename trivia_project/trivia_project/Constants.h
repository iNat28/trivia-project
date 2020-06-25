#pragma once
#include "pch.h"

//TODO: Move Codes to own file

enum class Codes
{
	ERROR_CODE = 0,

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
	USER_STATS = 30,
	HIGH_SCORES
};

enum class ResponseCodes
{
	ERROR_RESPONSE,
	SUCCESFUL
};

typedef char Byte;
typedef std::vector<Byte> Buffer;

#define MSG_CODE_SIZE sizeof(Byte)
#define MSG_LEN_SIZE 4 * sizeof(Byte)