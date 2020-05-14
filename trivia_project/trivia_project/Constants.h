
#pragma once
#include "pch.h"

enum class Codes
{
	ERROR_CODE,

	LOGIN = 10,
	SIGNUP
};

typedef char Byte;
typedef std::vector<Byte> Buffer;

#define MSG_CODE_SIZE sizeof(Byte)
#define MSG_LEN_SIZE 4 * sizeof(Byte)