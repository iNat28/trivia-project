#include "pch.h"
#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& errResponse)
{
	json jsonToSerialize;
	jsonToSerialize[Keys::message] = errResponse.message;

	return JsonResponsePacketSerializer::serializeJson(jsonToSerialize, Codes::ERROR_CODE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LoginResponse& loginResponse)
{
	return JsonResponsePacketSerializer::serializeStatusResponse(loginResponse, Codes::LOGIN);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const SignupResponse& signupResponse)
{
	return JsonResponsePacketSerializer::serializeStatusResponse(signupResponse, Codes::SIGNUP);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LogoutResponse& logoutResponse)
{
	return JsonResponsePacketSerializer::serializeStatusResponse(logoutResponse, Codes::LOGOUT);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetRoomResponse& getRoomResponse)
{
	json jsonToSerialize;
	jsonToSerialize[Keys::rooms] = getRoomResponse.rooms;

	return JsonResponsePacketSerializer::serializeJson(jsonToSerialize, Codes::GET_ROOM);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetPlayersInRoomResponse& getPlayersInRoomResponse)
{
	json jsonToSerialize;
	jsonToSerialize[Keys::rooms] = getPlayersInRoomResponse.rooms;

	return JsonResponsePacketSerializer::serializeJson(jsonToSerialize, Codes::GET_PLAYERS_IN_ROOM);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const JoinRoomReponse& joinRoomResponse)
{
	return JsonResponsePacketSerializer::serializeStatusResponse(joinRoomResponse, Codes::JOIN_ROOM);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const CreateRoomReponse& createRoomResponse)
{
	return JsonResponsePacketSerializer::serializeStatusResponse(createRoomResponse, Codes::CREATE_ROOM);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetStatisticsResponse& highScoreResponse)
{
	json jsonToSerialize;
	jsonToSerialize[Keys::userStatistics] = highScoreResponse.userStatistics;
	jsonToSerialize[Keys::highScores] = highScoreResponse.highScores;

	return JsonResponsePacketSerializer::serializeJson(jsonToSerialize, Codes::HIGH_SCORE);
}

Buffer JsonResponsePacketSerializer::serializeStatusResponse(const StatusResponse& statusResponse, Codes responseCode)
{
	json jsonToSerialize;
	jsonToSerialize[Keys::status] = statusResponse.status;

	return JsonResponsePacketSerializer::serializeJson(jsonToSerialize, responseCode);
}

Buffer JsonResponsePacketSerializer::serializeJson(const json& j, Codes responseCode)
{
	std::vector<unsigned char> jsonBuffer = json::to_bson(j);
	Buffer totalBuffer;
	char sizeBuffer[MSG_LEN_SIZE] = "";

	//Adds the response code
	totalBuffer.push_back(static_cast<Byte>(responseCode));

	//Adds the json message with the number of bytes
	totalBuffer.insert(totalBuffer.end(), jsonBuffer.begin(), jsonBuffer.end());
	return totalBuffer;
}

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

const char* Keys::status = "status";
const char* Keys::message = "message";

const char* Keys::rooms = "Rooms";
const char* Keys::playersInRoom = "PlayersInRoom";

const char* Keys::userStatistics = "UserStatistics";
const char* Keys::highScores = "HighScores";

const char* Keys::id = "id";
const char* Keys::name = "name";
const char* Keys::maxPlayers = "maxPlayers";
const char* Keys::timePerQuestion = "timePerQuestion";
const char* Keys::isActive = "isActive";