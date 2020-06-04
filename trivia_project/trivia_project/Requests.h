#pragma once

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
};

struct JoinRoomRequest : RoomIdRequest
{
};

struct CreateRoomRequest
{
	CreateRoomRequest(string roomName, unsigned int maxUsers, unsigned int questionCount, unsigned int answerTimeout);

	string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};