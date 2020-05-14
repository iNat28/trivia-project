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
	case Codes::LOGIN:
		requestResult = this->_login(requestInfo);
		break;
	case Codes::SIGNUP:
		requestResult = this->_signup(requestInfo);
		break;
	}

	return requestResult;
}

RequestResult LoginRequestHandler::_login(const RequestInfo& requestInfo)
{
	RequestResult requestResult;

	try
	{
		LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
		try {
			this->m_handlerFactor.getLoginManager().login(loginRequest.username, loginRequest.password);
			requestResult = RequestResult(JsonResponsePacketSerializer::serializeResponse(LoginResponse(1)), m_handlerFactor.createMenuRequestHandler());
		}
		catch (const std::exception & e)
		{
			requestResult = RequestResult(JsonResponsePacketSerializer::serializeResponse(ErrorResponse(e.what())), m_handlerFactor.createLoginRequestHandler());
		}
	}
	catch (...)
	{
		requestResult = RequestResult(JsonResponsePacketSerializer::serializeResponse(ErrorResponse("Error deserializing request")), m_handlerFactor.createLoginRequestHandler());
	}
	

	return requestResult;
}

RequestResult LoginRequestHandler::_signup(const RequestInfo& requestInfo)
{
	RequestResult requestResult;

	try
	{
		SignupRequest signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buffer);
		try {
			this->m_handlerFactor.getLoginManager().signup(signupRequest.username, signupRequest.password, signupRequest.email);
			requestResult = RequestResult(JsonResponsePacketSerializer::serializeResponse(SignupResponse(1)), m_handlerFactor.createMenuRequestHandler());
		}
		catch (const std::exception & e)
		{
			requestResult = RequestResult(JsonResponsePacketSerializer::serializeResponse(ErrorResponse(e.what())), m_handlerFactor.createLoginRequestHandler());
		}
	}
	catch (...)
	{
		requestResult = RequestResult(JsonResponsePacketSerializer::serializeResponse(ErrorResponse("Error deserializing request")), m_handlerFactor.createLoginRequestHandler());
	}

	return requestResult;
}

//
//template <typename T>
//RequestResult LoginRequestHandler::_loginAll(bool ifSuccess)
//{
//	LoginRequestHandler::ResponseCodes response = LoginRequestHandler::ResponseCodes::ERROR_RESPONSE;
//	IRequestHandlerPtr handler;
//	
//	if (ifSuccess)
//	{
//		handler = m_handlerFactor.createMenuRequestHandler();
//		response = LoginRequestHandler::ResponseCodes::SUCCESFUL;
//	}
//	else
//	{
//		handler = m_handlerFactor.createLoginRequestHandler();
//		response = LoginRequestHandler::ResponseCodes::USER_ALREADY_IN;
//	}
//
//	return RequestResult(JsonResponsePacketSerializer::serializeResponse(LoginResponse(static_cast<unsigned int>(response))), handler);
//}
//

