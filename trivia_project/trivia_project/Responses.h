#pragma once
#include "pch.h"
#include "Room.h"
#include "Constants.h"

struct Response
{
	virtual Codes getResponseCode() const = 0;
};

struct ErrorResponse : Response
{
	ErrorResponse(std::string message);

	virtual Codes getResponseCode() const override;

	std::string message;
};

struct StatusResponse : Response
{
	StatusResponse(unsigned int status);

	unsigned int status;
};

struct LoginResponse : StatusResponse
{
	using StatusResponse::StatusResponse;

	virtual Codes getResponseCode() const override;
};

struct SignupResponse : StatusResponse
{
	using StatusResponse::StatusResponse;

	virtual Codes getResponseCode() const override;
};

struct LogoutResponse : StatusResponse
{
	using StatusResponse::StatusResponse;

	virtual Codes getResponseCode() const override;
};

struct GetRoomResponse : StatusResponse
{
	GetRoomResponse(unsigned int status, vector<RoomData> rooms);

	virtual Codes getResponseCode() const override;

	vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse : Response
{
	GetPlayersInRoomResponse(vector<string> rooms);

	virtual Codes getResponseCode() const override;

	vector<string> rooms;
};

struct JoinRoomReponse : StatusResponse
{
	using StatusResponse::StatusResponse;

	virtual Codes getResponseCode() const override;
};

struct CreateRoomReponse : StatusResponse
{
	virtual Codes getResponseCode() const override;

	using StatusResponse::StatusResponse;
};

struct GetStatisticsResponse : StatusResponse
{
	GetStatisticsResponse(unsigned int status, vector<string> userStatistics, vector<string> highScores);

	virtual Codes getResponseCode() const override;

	vector<string> userStatistics;
	vector<string> highScores;
};