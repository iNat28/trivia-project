
#pragma once
#include "pch.h"

enum class RequestCodes
{
	ERROR_REQUEST = 0,

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

typedef char Byte;
typedef std::vector<Byte> Buffer;

#define MSG_CODE_SIZE sizeof(Byte)
#define MSG_LEN_SIZE 4 * sizeof(Byte)