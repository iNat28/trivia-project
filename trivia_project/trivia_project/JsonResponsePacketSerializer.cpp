#include "pch.h"
#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& errResponse)
{
	json jsonToSerialize;
	jsonToSerialize[ErrorResponse::messageKey] = errResponse.message;

	return JsonResponsePacketSerializer::serializeJson(jsonToSerialize, Codes::ERROR_CODE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LoginResponse& loginResponse)
{
	return JsonResponsePacketSerializer::serializeResponse(loginResponse, Codes::LOGIN);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const SignupResponse& signupResponse)
{
	return JsonResponsePacketSerializer::serializeResponse(signupResponse, Codes::SIGNUP);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LogoutResponse& logoutResponse)
{
	return JsonResponsePacketSerializer::serializeResponse(logoutResponse, Codes::LOGOUT);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetRoomResponse& getRoomResponse)
{
	json jsonToSerialize;
	jsonToSerialize[GetRoomResponse::roomsKey] = getRoomResponse.rooms;

	return JsonResponsePacketSerializer::serializeJson(jsonToSerialize, Codes::GET_ROOM);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetPlayersInRoomResponse& getPlayersInRoomResponse)
{
	json jsonToSerialize;
	jsonToSerialize[GetRoomResponse::roomsKey] = getPlayersInRoomResponse.users;

	return JsonResponsePacketSerializer::serializeJson(jsonToSerialize, Codes::GET_PLAYERS_IN_ROOM);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const JoinRoomReponse& joinRoomResponse)
{
	return JsonResponsePacketSerializer::serializeResponse(joinRoomResponse, Codes::JOIN_ROOM);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const CreateRoomReponse& createRoomResponse)
{
	return JsonResponsePacketSerializer::serializeResponse(createRoomResponse, Codes::CREATE_ROOM);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const HighScoreResponse& highScoreResponse)
{
	json jsonToSerialize;
	jsonToSerialize[HighScoreResponse::userStatisticsKey] = highScoreResponse.userStatistics;
	jsonToSerialize[HighScoreResponse::highScoresKey] = highScoreResponse.highScores;

	return JsonResponsePacketSerializer::serializeJson(jsonToSerialize, Codes::HIGH_SCORE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const StatusResponse& statusResponse, Codes responseCode)
{
	json jsonToSerialize;
	jsonToSerialize[StatusResponse::statusKey] = statusResponse.status;

	return JsonResponsePacketSerializer::serializeJson(jsonToSerialize, responseCode);
}

Buffer JsonResponsePacketSerializer::serializeJson(const json& j, Codes responseCode)
{
	std::vector<unsigned char> jsonBuffer = json::to_bson(j);
	Buffer totalBuffer;
	char sizeBuffer[MSG_LEN_SIZE] = "";
	int jsonSize = jsonBuffer.size();

	//Adds the response code
	totalBuffer.push_back(static_cast<Byte>(responseCode));

	//Adds the json message with the number of bytes
	totalBuffer.insert(totalBuffer.end(), jsonBuffer.begin(), jsonBuffer.end());
	return totalBuffer;
}

//Keys
const char* StatusResponse::statusKey = "status";
const char* ErrorResponse::messageKey = "message";
const char* GetRoomResponse::roomsKey = "Rooms";
const char* GetPlayersInRoomResponse::usersKey = "PlayersInRoom";
const char* HighScoreResponse::userStatisticsKey = "UserStatistics";
const char* HighScoreResponse::highScoresKey = "HighScores";

StatusResponse::StatusResponse(unsigned int status) :
	status(status)
{
}

ErrorResponse::ErrorResponse(std::string message) :
	message(message)
{
}

GetRoomResponse::GetRoomResponse(vector<string> rooms) :
	rooms(rooms)
{
}

GetPlayersInRoomResponse::GetPlayersInRoomResponse(vector<string> users) :
	users(users)
{
}

HighScoreResponse::HighScoreResponse(vector<string> userStatistics, vector<string> highScores) : 
	userStatistics(userStatistics), highScores(highScores)
{
}
