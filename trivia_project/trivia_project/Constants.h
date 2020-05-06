#pragma once
#include "pch.h"

enum class RequestCodes
{
	//Login codes
	LOGIN_REQUEST = 10,
	SIGNUP_REQUEST
};

enum class ResponseCodes
{
	//Errors
	ERROR_RESPONSE = 0,

	//Login codes
	LOGIN_RESPONSE = 10,
	SIGNUP_RESPONSE
};

typedef std::uint8_t Byte;
typedef std::vector<Byte> Buffer;