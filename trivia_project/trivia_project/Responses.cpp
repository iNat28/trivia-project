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

GetStatisticsResponse::GetStatisticsResponse(unsigned int status, vector<string> userStatistics, vector<string> highScores) :
	StatusResponse(status), userStatistics(userStatistics), highScores(highScores)
{
}

Codes GetStatisticsResponse::getResponseCode() const
{
	return Codes::STATISTICS;
}