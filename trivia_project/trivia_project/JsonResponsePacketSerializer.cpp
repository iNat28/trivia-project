#include "JsonResponsePacketSerializer.h"

vector<Byte> JsonResponsePacketSerializer::serializeResponse(ErrorResponse)
{
	json j;
	j["message"] = "ERROR";
	vector<Byte> v_bson = json::to_bson(j);
	//need to choose code for each response and put it first, then add the length of the json object and then add the message
	return v_bson;
}

vector<Byte> JsonResponsePacketSerializer::serializeResponse(LoginResponse)
{
	json j;
	j["status"] = 1;
	vector<Byte> v_bson = json::to_bson(j);
	return v_bson;
}

vector<Byte> JsonResponsePacketSerializer::serializeResponse(SignupResponse)
{
	json j;
	j["status"] = 1;
	vector<Byte> v_bson = json::to_bson(j);
	return v_bson;
}
