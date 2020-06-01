#pragma once
#include "pch.h"
#include "Responses.h"
#include "Constants.h"

class JsonResponsePacketSerializer
{
public:
	static Buffer serializeResponse(const ErrorResponse& errorResponse);
	static Buffer serializeResponse(const StatusResponse& statusResponse);
	static Buffer serializeResponse(const GetRoomResponse& getRoomResponse);
	static Buffer serializeResponse(const GetPlayersInRoomResponse& getPlayersInRoomResponse);
	static Buffer serializeResponse(const GetStatisticsResponse& getStatisticsResponse);

private:
	static Buffer serializeJson(const json& jsonToSerialize, const Response& response);
};

void to_json(json& j, const RoomData& roomData);
void from_json(const json& j, RoomData& roomData);

struct Keys
{
	static const char* message;
	static const char* status;

	//Rooms
	static const char* rooms;
	static const char* playersInRoom;

	//Statistics
	static const char* userStatistics;
	static const char* highScores;

	//RoomData
	static const char* id;
	static const char* name;
	static const char* maxPlayers;
	static const char* timePerQuestion;
	static const char* isActive;
};