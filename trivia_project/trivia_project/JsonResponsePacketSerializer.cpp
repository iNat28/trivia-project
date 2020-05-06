#include "pch.h"
#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse errResponse)
{
	json j;
	j["message"] = errResponse.message;
	Buffer v_bson = json::to_bson(j);
	Buffer v_cson;
	v_cson.push_back(Byte(ResponseCodes::ERROR_RESPONSE));
	//v_cson.push_back(Byte(j.size()));
	int length = j.size();
	char* chars = reinterpret_cast<char*>(&length);
	v_cson.insert(v_cson.end(), chars, chars + sizeof(int));
	v_cson.insert(v_cson.end(), v_bson.begin(), v_bson.end());
	return v_cson;
}

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse loginResponse)
{
	json j;
	j["status"] = loginResponse.status;
	Buffer v_bson = json::to_bson(j);
	Buffer v_cson;
	v_cson.push_back(Byte(ResponseCodes::LOGIN_RESPONSE));
	v_cson.push_back(Byte(j.size()));
	v_cson.insert(v_cson.end(), v_bson.begin(), v_bson.end());
	return v_cson;
}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse signupResponse)
{
	json j;
	j["status"] = signupResponse.status;
	Buffer v_bson = json::to_bson(j);
	Buffer v_cson;
	v_cson.push_back(Byte(ResponseCodes::SIGNUP_RESPONSE));
	v_cson.push_back(Byte(j.size()));
	v_cson.insert(v_cson.end(), v_bson.begin(), v_bson.end());
	return v_cson;
}


