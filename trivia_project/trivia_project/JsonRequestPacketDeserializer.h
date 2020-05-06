#pragma once
#include "pch.h"
#include "Constants.h"

#define REQUEST_MSG_CODE_SIZE sizeof(Byte)
#define REQUEST_MSG_LEN_SIZE 4 * sizeof(Byte)

struct LoginRequest
{
	std::string username;
	std::string password;
};

struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
};

class JsonRequestPacketDeserializer
{
	static LoginRequest deserializeLoginRequest(const Buffer& buffer);
	static SignupRequest deserializeSignupRequest(const Buffer& buffer);
};