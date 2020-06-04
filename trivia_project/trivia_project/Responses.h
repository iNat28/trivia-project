#pragma once
#include "pch.h"
#include "Room.h"

struct ErrorResponse
{
	ErrorResponse(std::string message);

	std::string message;
};

struct StatusResponse
{
	StatusResponse(unsigned int status);

	unsigned int status;
};

struct LoginResponse : StatusResponse
{
	using StatusResponse::StatusResponse;
};

struct SignupResponse : StatusResponse
{
	using StatusResponse::StatusResponse;
};

struct LogoutResponse : StatusResponse
{
	using StatusResponse::StatusResponse;
};

struct GetRoomResponse : StatusResponse
{
	GetRoomResponse(unsigned int status, vector<RoomData> rooms);

	vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse
{
	GetPlayersInRoomResponse(vector<string> rooms);

	vector<string> rooms;
};

struct JoinRoomReponse : StatusResponse
{
	using StatusResponse::StatusResponse;
};

struct CreateRoomReponse : StatusResponse
{
	using StatusResponse::StatusResponse;
};

struct GetStatisticsResponse : StatusResponse
{
	GetStatisticsResponse(unsigned int status, vector<string> userStatistics, vector<string> highScores);

	vector<string> userStatistics;
	vector<string> highScores;
};