#include "pch.h"
#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse errResponse)
{
	json j;
	j["message"] = errResponse.message;
	Buffer v_bson = json::to_bson(j);
	//need to choose code for each response and put it first, then add the length of the json object and then add the message
	return v_bson;
}

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse loginResponse)
{
	json j;
	j["status"] = loginResponse.status;
	Buffer v_bson = json::to_bson(j);
	return v_bson;
}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse signupResponse)
{
	json j;
	j["status"] = signupResponse.status;
	Buffer v_bson = json::to_bson(j);
	return v_bson;
}

