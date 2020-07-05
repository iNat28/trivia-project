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
	GET_ROOM_STATE,

	//RoomAdmin
	CLOSE_ROOM = 30,
	START_GAME,

	//RoomMember
	LEAVE_ROOM = 40,

	//Statistics
	USER_STATS = 50,
	HIGH_SCORES
};

enum class ResponseCodes
{
	ERROR_RESPONSE,
	SUCCESFUL
};