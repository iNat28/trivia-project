#include "JsonRequestPacketDeserializer.h"
/*
Usage: this fucntion gets a vector of bytes and makes it into a login struct using deserialization.
Input: vector<Byte>.
Output: LoginRequest object.
*/
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(vector<Byte> Buffer)
{
	//over here we would have to cut off the first 6 bytes that are the msg code and the size, the rest we can use in this function
	json j_from_bson = json::from_bson(Buffer);
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
SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(vector<Byte> Buffer)
{
	json j_from_bson = json::from_bson(Buffer);
	SignupRequest userSignupInfo = SignupRequest();
	userSignupInfo.username = j_from_bson["username"];
	userSignupInfo.password = j_from_bson["password"];
	userSignupInfo.email = j_from_bson["email"];
	return userSignupInfo;
}
