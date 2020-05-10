#include "pch.h"
#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler()
{
}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
	return true;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	Buffer responseBuffer;
	
	switch (requestInfo.requestId)
	{
	case RequestCodes::LOGIN_REQUEST:
		responseBuffer = handleLoginRequest(requestInfo.buffer);
		break;
	case RequestCodes::SIGNUP_REQUEST:
		responseBuffer = handleSignupRequest(requestInfo.buffer);
		break;
	}
	return RequestResult(responseBuffer, nullptr);
}

Buffer LoginRequestHandler::handleLoginRequest(const Buffer& buffer)
{
	unsigned int response = 1;

	try {
		LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(buffer);
	}
	catch (const std::exception & e)
	{
		unsigned int response = 0;
	}

	return JsonResponsePacketSerializer::serializeResponse(LoginResponse{ response });
}

Buffer LoginRequestHandler::handleSignupRequest(const Buffer& buffer)
{
	unsigned int response = 1;

	try {
		SignupRequest signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(buffer);
	}
	catch (const std::exception & e)
	{
		unsigned int response = 0;
	}
	
	return JsonResponsePacketSerializer::serializeResponse(SignupResponse{ response });
}
