#include "pch.h"
#include "JsonRequestPacketDeserializer.h"

/*
Usage: this fucntion gets a vector of bytes and makes it into a login struct using deserialization.
Input: vector<Byte>.
Output: LoginRequest object.
*/
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const Buffer& buffer)
{
	json j_from_bson = json::from_bson(buffer);
	LoginRequest userLoginInfo = LoginRequest();
	userLoginInfo.username = j_from_bson["username"];
	userLoginInfo.password = j_from_bson["password"];
	return userLoginInfo;
}
/*
Usage: this fucntion gets a vector of bytes and makes it into a signup struct using deserialization.
Input: vector<Byte>.
Output: SignupRequest object.
*/
SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const Buffer& buffer)
{
	json j_from_bson = json::from_bson(buffer);

	SignupRequest userSignupInfo = SignupRequest();
	userSignupInfo.username = j_from_bson["username"];
	userSignupInfo.password = j_from_bson["password"];
	userSignupInfo.email = j_from_bson["email"];
	return userSignupInfo;
}
