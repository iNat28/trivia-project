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

GetRoomResponse::GetRoomResponse(unsigned int status, vector<RoomData> rooms) :
	StatusResponse(status), rooms(rooms)
{
}

GetPlayersInRoomResponse::GetPlayersInRoomResponse(vector<string> users) :
	rooms(users)
{
}

GetStatisticsResponse::GetStatisticsResponse(unsigned int status, vector<string> userStatistics, vector<string> highScores) :
	StatusResponse(status), userStatistics(userStatistics), highScores(highScores)
{
}