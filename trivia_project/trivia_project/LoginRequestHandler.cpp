#include "pch.h"
#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactor) :
	m_handlerFactor(handlerFactor)
{
}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
	return true;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	RequestResult requestResult;
	
	switch (requestInfo.requestId)
	{
	case RequestCodes::LOGIN_REQUEST:
		requestResult = this->_login(requestInfo);
		break;
	case RequestCodes::SIGNUP_REQUEST:
		requestResult = this->_signup(requestInfo);
		break;
	}

	return requestResult;
}

RequestResult LoginRequestHandler::_login(const RequestInfo& requestInfo)
{
	unsigned int response = 1;

	try {
		LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
	}
	catch (const std::exception & e)
	{
		unsigned int response = 0;
	}

	return RequestResult(JsonResponsePacketSerializer::serializeResponse(LoginResponse{ response }), nullptr);
}

RequestResult LoginRequestHandler::_signup(const RequestInfo& requestInfo)
{
	unsigned int response = 1;

	try {
		SignupRequest signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buffer);
	}
	catch (const std::exception & e)
	{
		unsigned int response = 0;
	}
	
	return RequestResult(JsonResponsePacketSerializer::serializeResponse(SignupResponse{ response }), nullptr);
}
