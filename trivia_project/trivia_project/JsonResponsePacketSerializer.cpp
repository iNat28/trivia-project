#include "pch.h"
#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& errResponse)
{
	json jsonToSerialize;
	jsonToSerialize[Keys::message] = errResponse.message;

	return JsonResponsePacketSerializer::serializeJson(jsonToSerialize, errResponse);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetRoomResponse& getRoomResponse)
{
	json jsonToSerialize;
	jsonToSerialize[Keys::rooms] = getRoomResponse.rooms;

	return JsonResponsePacketSerializer::serializeJson(jsonToSerialize, getRoomResponse);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetPlayersInRoomResponse& getPlayersInRoomResponse)
{
	json jsonToSerialize;
	jsonToSerialize[Keys::playersInRoom] = getPlayersInRoomResponse.users;

	return JsonResponsePacketSerializer::serializeJson(jsonToSerialize, getPlayersInRoomResponse);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetUserStatsResponse& getUserStatsResponse)
{
	json jsonToSerialize;
	jsonToSerialize[Keys::userStats] = getUserStatsResponse.userStats;
	jsonToSerialize[Keys::status] = getUserStatsResponse.status;

	return JsonResponsePacketSerializer::serializeJson(jsonToSerialize, getUserStatsResponse);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetHighScoresResponse& getHighScoresResponse)
{
	json jsonToSerialize;
	jsonToSerialize[Keys::highScores] = getHighScoresResponse.highScores;
	jsonToSerialize[Keys::status] = getHighScoresResponse.status;

	return JsonResponsePacketSerializer::serializeJson(jsonToSerialize, getHighScoresResponse);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const StatusResponse& statusResponse)
{
	json jsonToSerialize;
	jsonToSerialize[Keys::status] = statusResponse.status;

	return JsonResponsePacketSerializer::serializeJson(jsonToSerialize, statusResponse);
}

Buffer JsonResponsePacketSerializer::serializeJson(const json& jsonToSerialize, const Response& response)
{
	std::vector<unsigned char> jsonBuffer = json::to_bson(jsonToSerialize);
	Buffer totalBuffer;
	char sizeBuffer[MSG_LEN_SIZE] = "";

	//Adds the response code
	totalBuffer.push_back(static_cast<Byte>(response.getResponseCode()));

	//Adds the json message with the number of bytes
	totalBuffer.insert(totalBuffer.end(), jsonBuffer.begin(), jsonBuffer.end());
	return totalBuffer;
}