#pragma once
#include "pch.h"
#include "Constants.h"

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
	std::string message;
};


class JsonResponsePacketSerializer
{
public:
	static Buffer serializeResponse(ErrorResponse errResponse);
	static Buffer serializeResponse(LoginResponse loginResponse);
	static Buffer serializeResponse(SignupResponse signupResponse);
};
