#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;
typedef unsigned char Byte;

class JsonRequestPacketDeserializer
{
	static LoginRequest deserializeLoginRequest(vector<Byte> Buffer);
	static SignupRequest deserializeSignupRequest(vector<Byte> Buffer);
};

typedef struct LoginRequest
{
	string username;
	string password;
} LoginRequest;

typedef struct SignupRequest
{
	string username;
	string password;
	string email;
} SignupRequest;
