#pragma once
#include <string>
#include <vector>
#include "json.hpp"

using std::string;
using std::vector;
typedef std::uint8_t Byte;

class JsonRequestPacketDeserializer
{
	static LoginRequest deserializeLoginRequest(vector<Byte> Buffer);
	static SignupRequest deserializeSignupRequest(vector<Byte> Buffer);
};

struct LoginRequest
{
	string username;
	string password;
};

struct SignupRequest
{
	string username;
	string password;
	string email;
};
