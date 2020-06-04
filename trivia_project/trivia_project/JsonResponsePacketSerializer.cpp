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
	jsonToSerialize[Keys::rooms] = getPlayersInRoomResponse.rooms;

	return JsonResponsePacketSerializer::serializeJson(jsonToSerialize, getPlayersInRoomResponse);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetStatisticsResponse& getStatisticsResponse)
{
	json jsonToSerialize;
	jsonToSerialize[Keys::userStatistics] = getStatisticsResponse.userStatistics;
	jsonToSerialize[Keys::highScores] = getStatisticsResponse.highScores;

	return JsonResponsePacketSerializer::serializeJson(jsonToSerialize, getStatisticsResponse);
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

//For RoomData
inline void to_json(json& j, const RoomData& roomData)
{
	j[Keys::id] = roomData.id;
	j[Keys::name] = roomData.name;
	j[Keys::maxPlayers] = roomData.maxPlayers;
	j[Keys::timePerQuestion] = roomData.timePerQuestion;
	j[Keys::isActive] = roomData.isActive;
}

inline void from_json(const json& j, RoomData& roomData)
{
	roomData = RoomData(
		j[Keys::id],
		j[Keys::name],
		j[Keys::maxPlayers],
		j[Keys::timePerQuestion],
		j[Keys::isActive]
	);
}