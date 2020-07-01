#include "pch.h"
#include "Responses.h"

StatusResponse::StatusResponse(unsigned int status) :
	status(status)
{
}

ErrorResponse::ErrorResponse(std::string message) :
	message(message)
{
}

Codes LoginResponse::getResponseCode() const
{
	return Codes::LOGIN;
}

Codes SignupResponse::getResponseCode() const
{
	return Codes::SIGNUP;
}

Codes LogoutResponse::getResponseCode() const
{
	return Codes::LOGOUT;
}

Codes ErrorResponse::getResponseCode() const
{
	return Codes::ERROR_CODE;
}

GetRoomResponse::GetRoomResponse(unsigned int status, vector<Room> rooms) :
	StatusResponse(status), rooms(rooms)
{
}

Codes GetRoomResponse::getResponseCode() const
{
	return Codes::GET_ROOM;
}

GetPlayersInRoomResponse::GetPlayersInRoomResponse(vector<LoggedUser> users) :
	users(users)
{
}

Codes GetPlayersInRoomResponse::getResponseCode() const
{
	return Codes::GET_PLAYERS_IN_ROOM;
}

Codes JoinRoomResponse::getResponseCode() const
{
	return Codes::JOIN_ROOM;
}

Codes CreateRoomResponse::getResponseCode() const
{
	return Codes::CREATE_ROOM;
}

GetUserStatsResponse::GetUserStatsResponse(unsigned int status, UserStats userStats) : 
	StatusResponse(status), userStats(userStats)
{
}

Codes GetUserStatsResponse::getResponseCode() const
{
	return Codes::USER_STATS;
}

GetHighScoresResponse::GetHighScoresResponse(unsigned int status, HighScores highScores) : 
	StatusResponse(status), highScores(highScores)
{
}

Codes GetHighScoresResponse::getResponseCode() const
{
	return Codes::HIGH_SCORES;
}

Codes CloseRoomResponse::getResponseCode() const
{
	return Codes::CLOSE_ROOM;
}

Codes LeaveRoomResponse::getResponseCode() const
{
	return Codes::LEAVE_ROOM;
}
