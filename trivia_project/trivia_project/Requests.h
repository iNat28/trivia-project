#pragma once
#include "Room.h"

struct LoginRequest
{
	LoginRequest(string username, string password);

	string username;
	string password;
};

struct SignupRequest : LoginRequest
{
	SignupRequest(string username, string password, string email);

	string email;
};

struct RoomIdRequest
{
	RoomIdRequest(unsigned int roomId);

	unsigned int roomId;
};

struct GetPlayersInRoomRequest : RoomIdRequest
{
	using RoomIdRequest::RoomIdRequest;
};

struct JoinRoomRequest : RoomIdRequest
{
	using RoomIdRequest::RoomIdRequest;
};

struct CreateRoomRequest
{
	CreateRoomRequest(RoomData roomData);

	RoomData roomData;
};