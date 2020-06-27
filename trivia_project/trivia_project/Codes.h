#pragma once

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
	CLOSE_ROOM,

	//Statistics
	USER_STATS = 30,
	HIGH_SCORES
};

enum class ResponseCodes
{
	ERROR_RESPONSE,
	SUCCESFUL
};

