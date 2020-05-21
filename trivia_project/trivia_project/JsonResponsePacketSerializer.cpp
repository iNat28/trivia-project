#include "pch.h"
#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& errResponse)
{
	json j;
	j["message"] = errResponse.message;

	return JsonResponsePacketSerializer::serializeJson(j, Codes::ERROR_CODE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LoginResponse& loginResponse)
{
	json j;
	j["status"] = loginResponse.status;

	return JsonResponsePacketSerializer::serializeJson(j, Codes::LOGIN);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const SignupResponse& signupResponse)
{
	json j;
	j["status"] = signupResponse.status;

	return JsonResponsePacketSerializer::serializeJson(j, Codes::SIGNUP);
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


LoginResponse::LoginResponse(unsigned int status) : 
	status(status)
{
}

LoginResponse::LoginResponse() :
	status(0)
{
}

SignupResponse::SignupResponse(unsigned int status) :
	status(status)
{
}

SignupResponse::SignupResponse() :
	status(0)
{
}

ErrorResponse::ErrorResponse(std::string message) :
	message(message)
{
}

ErrorResponse::ErrorResponse() :
	message()
{
}
