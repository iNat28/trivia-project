#pragma once
#include "pch.h"
#include "Room.h"
#include "Codes.h"

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
	GetRoomResponse(unsigned int status, vector<Room> rooms);

	virtual Codes getResponseCode() const override;

	vector<Room> rooms;
};

struct GetPlayersInRoomResponse : Response
{
	GetPlayersInRoomResponse(vector<LoggedUser> rooms);

	virtual Codes getResponseCode() const override;

	vector<LoggedUser> users;
};

struct GetUserStatsResponse : StatusResponse
{
	GetUserStatsResponse(unsigned int status, UserStats userStats);

	virtual Codes getResponseCode() const override;

	UserStats userStats;
};

struct GetHighScoresResponse : StatusResponse
{
	GetHighScoresResponse(unsigned int status, HighScores highScores);

	virtual Codes getResponseCode() const override;

	HighScores highScores;
};

struct JoinRoomResponse : StatusResponse
{
	using StatusResponse::StatusResponse;

	virtual Codes getResponseCode() const override;
};

struct CreateRoomResponse : StatusResponse
{
	virtual Codes getResponseCode() const override;

	using StatusResponse::StatusResponse;
};

struct CloseRoomResponse : StatusResponse
{
	virtual Codes getResponseCode() const override;

	using StatusResponse::StatusResponse;
};

struct LeaveRoomResponse : StatusResponse
{
	virtual Codes getResponseCode() const override;

	using StatusResponse::StatusResponse;
};