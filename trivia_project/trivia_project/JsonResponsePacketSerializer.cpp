#include "pch.h"
#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& errResponse)
{
	json j;
	j["message"] = errResponse.message;

	return JsonResponsePacketSerializer::serializeJson(j, ResponseCodes::ERROR_RESPONSE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LoginResponse& loginResponse)
{
	json j;
	j["status"] = loginResponse.status;

	return JsonResponsePacketSerializer::serializeJson(j, ResponseCodes::LOGIN_RESPONSE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const SignupResponse& signupResponse)
{
	json j;
	j["status"] = signupResponse.status;

	return JsonResponsePacketSerializer::serializeJson(j, ResponseCodes::SIGNUP_RESPONSE);
}

Buffer JsonResponsePacketSerializer::serializeJson(const json& j, ResponseCodes responseCode)
{
	std::vector<unsigned char> jsonBuffer = json::to_bson(j);
	Buffer totalBuffer;
	char sizeBuffer[MSG_LEN_SIZE] = "";
	int jsonSize = jsonBuffer.size();
	
	//Adds the response code
	totalBuffer.push_back(static_cast<Byte>(responseCode));

	//Adds the message lengths as bytes
	//memcpy_s(sizeBuffer, MSG_LEN_SIZE, &jsonSize, sizeof(int));
	//totalBuffer.insert(totalBuffer.end(), sizeBuffer, sizeBuffer + MSG_LEN_SIZE);

	//Adds the json message
	totalBuffer.insert(totalBuffer.end(), jsonBuffer.begin(), jsonBuffer.end());
	return totalBuffer;
}