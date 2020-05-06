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
	static Buffer serializeResponse(ErrorResponse);
	static Buffer serializeResponse(LoginResponse);
	static Buffer serializeResponse(SignupResponse);
};