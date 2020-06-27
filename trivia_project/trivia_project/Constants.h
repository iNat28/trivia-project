#pragma once
#include "pch.h"

//TODO: Move Codes to own file

typedef char Byte;
typedef std::vector<Byte> Buffer;

#define MSG_CODE_SIZE sizeof(Byte)
#define MSG_LEN_SIZE 4 * sizeof(Byte)