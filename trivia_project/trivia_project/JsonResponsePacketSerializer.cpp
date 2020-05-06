#include "pch.h"
#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse)
{
	json j;
	j["message"] = "ERROR";
	Buffer v_bson = json::to_bson(j);
	//need to choose code for each response and put it first, then add the length of the json object and then add the message
	return v_bson;
}

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse)
{
	json j;
	j["status"] = 1;
	Buffer v_bson = json::to_bson(j);
	return v_bson;
}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse)
{
	json j;
	j["status"] = 1;
	Buffer v_bson = json::to_bson(j);
	return v_bson;
}
