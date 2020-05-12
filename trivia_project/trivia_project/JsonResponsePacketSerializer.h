
#pragma once
#include "pch.h"
#include "Constants.h"

struct LoginResponse
{
	LoginResponse(unsigned int status);
	LoginResponse();

	unsigned int status;
};

struct SignupResponse
{
	SignupResponse(unsigned int status);
	SignupResponse();

	unsigned int status;
};

struct ErrorResponse
{
	ErrorResponse(std::string message);
	ErrorResponse();

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