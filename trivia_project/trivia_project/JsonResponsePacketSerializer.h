#pragma once
#include "pch.h"
#include "Constants.h"

struct ErrorResponse
{
	ErrorResponse(std::string message);

	static const char* messageKey;
	std::string message;
};

struct StatusResponse
{
	StatusResponse(unsigned int status);

	static const char* statusKey;
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

struct GetRoomResponse
{
	GetRoomResponse(vector<string> rooms);

	static const char* roomsKey;
	vector<string> rooms;
};

struct GetPlayersInRoomResponse
{
	GetPlayersInRoomResponse(vector<string> users);

	static const char* usersKey;
	vector<string> users;
};

struct JoinRoomReponse : StatusResponse
{
	using StatusResponse::StatusResponse;
};

struct CreateRoomReponse : StatusResponse
{
	using StatusResponse::StatusResponse;
};

struct HighScoreResponse
{
	HighScoreResponse(vector<string> userStatistics, vector<string> highScores);

	static const char* userStatisticsKey;
	static const char* highScoresKey;
	vector<string> userStatistics;
	vector<string> highScores;
};

class JsonResponsePacketSerializer
{
public:
	static Buffer serializeResponse(const ErrorResponse& errorResponse);
	static Buffer serializeResponse(const LoginResponse& loginResponse);
	static Buffer serializeResponse(const SignupResponse& signupResponse);
	static Buffer serializeResponse(const LogoutResponse& logoutResponse);
	static Buffer serializeResponse(const GetRoomResponse& getRoomResponse);
	static Buffer serializeResponse(const GetPlayersInRoomResponse& getPlayersInRoomResponse);
	static Buffer serializeResponse(const JoinRoomReponse& joinRoomResponse);
	static Buffer serializeResponse(const CreateRoomReponse& createRoomResponse);
	static Buffer serializeResponse(const HighScoreResponse& highScoreResponse);

private:
	static Buffer serializeResponse(const StatusResponse& statusResponse, Codes responseCode);
	static Buffer serializeJson(const json& j, Codes responseCode);
};