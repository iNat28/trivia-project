#include "pch.h"
#include "JsonRequestPacketDeserializer.h"

/*
Usage: this fucntion gets a vector of bytes and makes it into a login struct using deserialization.
Input: vector<Byte>.
Output: LoginRequest object.
*/
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const Buffer& buffer)
{
	json jsonFromBson = json::from_bson(buffer);
	LoginRequest userLoginInfo;

	userLoginInfo.username = jsonFromBson["username"];
	userLoginInfo.password = jsonFromBson["password"];

	return userLoginInfo;
}
/*
Usage: this fucntion gets a vector of bytes and makes it into a signup struct using deserialization.
Input: vector<Byte>.
Output: SignupRequest object.
*/
SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const Buffer& buffer)
{
	json jsonFromBson = json::from_bson(buffer);
	SignupRequest userSignupInfo;

	userSignupInfo.username = jsonFromBson["username"];
	userSignupInfo.password = jsonFromBson["password"];
	userSignupInfo.email = jsonFromBson["email"];

	return userSignupInfo;
}
