#pragma once
#include "pch.h"
#include "Responses.h"
#include "Constants.h"
#include "Keys.h"
#include "LoggedUser.h"
#include "Room.h"

class JsonResponsePacketSerializer
{
public:
	static Buffer serializeResponse(const ErrorResponse& errorResponse);
	static Buffer serializeResponse(const StatusResponse& statusResponse);
	static Buffer serializeResponse(const GetRoomResponse& getRoomResponse);
	static Buffer serializeResponse(const GetPlayersInRoomResponse& getPlayersInRoomResponse);
	static Buffer serializeResponse(const GetUserStatsResponse& getUserStatsResponse);
	static Buffer serializeResponse(const GetHighScoresResponse& getUserStatsResponse);
	static Buffer serializeResponse(const GetRoomStateResponse& getRoomStateResponse);

private:
	static Buffer serializeJson(const json& jsonToSerialize, const Response& response);
};