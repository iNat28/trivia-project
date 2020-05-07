#pragma once
#include "pch.h"
#include "Constants.h"
#include "JsonRequestPacketDeserializer.h"

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
	static Buffer serializeResponse(const ErrorResponse& errResponse);
	static Buffer serializeResponse(const LoginResponse& loginResponse);
	static Buffer serializeResponse(const SignupResponse& signupResponse);
private:
	static Buffer serializeJson(const json& j, ResponseCodes responseCode);
};