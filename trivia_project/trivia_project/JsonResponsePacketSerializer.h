#pragma once

#include <string>
#include <vector>
#include "json.hpp"

using std::string;
using std::vector;
using json = nlohmann::json;
typedef std::uint8_t Byte;

class JsonResponsePacketSerializer
{
	static vector<Byte> serializeResponse(ErrorResponse);
	static vector<Byte> serializeResponse(LoginResponse);
	static vector<Byte> serializeResponse(SignupResponse);
};

struct LoginResponse
{
	unsigned int status;
};

struct SignupResponse
{
	unsigned int status;
};

struct ErrorResponse
{
	string message;
};
