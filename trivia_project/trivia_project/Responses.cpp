#include "pch.h"
#include "Responses.h"

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

GetRoomResponse::GetRoomResponse(const vector<Room>& rooms) : 
	rooms(rooms)
{
}

Codes GetRoomResponse::getResponseCode() const
{
	return Codes::GET_ROOM;
}

GetPlayersInRoomResponse::GetPlayersInRoomResponse(const vector<LoggedUser>& players) :
	players(players)
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

GetUserStatsResponse::GetUserStatsResponse(const UserStats& userStats) : 
	userStats(userStats)
{
}

Codes GetUserStatsResponse::getResponseCode() const
{
	return Codes::USER_STATS;
}

GetHighScoresResponse::GetHighScoresResponse(const HighScores& highScores) : 
	highScores(highScores)
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

GetRoomStateResponse::GetRoomStateResponse(RoomStatus roomStatus, const vector<LoggedUser>& players) : 
	roomStatus(roomStatus), players(players)
{
}

Codes GetRoomStateResponse::getResponseCode() const
{
	return Codes::GET_ROOM_STATE;
}

Codes StartGameResponse::getResponseCode() const
{
	return Codes::START_GAME;
}
