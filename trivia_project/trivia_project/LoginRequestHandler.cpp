#include "pch.h"
#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactor) :
	m_handlerFactor(handlerFactor)
{
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo) const
{
	RequestResult requestResult;

	//If at any point the login or sign up doesn't work, an exception will be thrown, 
	//and it will be put into an error response
	try {
		switch (requestInfo.requestId)
		{
		case Codes::LOGIN:
			requestResult = this->_login(requestInfo);
			break;
		case Codes::SIGNUP:
			requestResult = this->_signup(requestInfo);
			break;
		default:
			throw Exception("Request Code not valid");
		}
	}
	//Login manager exception caught
	catch (const Exception& e)
	{
		requestResult = RequestResult(
			JsonResponsePacketSerializer::serializeResponse(ErrorResponse(e.what())),
			m_handlerFactor.createLoginRequestHandler());
	}
	//Other exception caught (probably because of the json)
	catch (...)
	{
		requestResult = RequestResult(
			JsonResponsePacketSerializer::serializeResponse(ErrorResponse("Unkown error occured")),
			nullptr);
	}

	return requestResult;
}

RequestResult LoginRequestHandler::_login(const RequestInfo& requestInfo) const
{
	LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
	
	//Throws an Exception if the login doesn't work
	this->m_handlerFactor.getLoginManager().login(loginRequest.username, loginRequest.password);

	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(LoginResponse(static_cast<unsigned int>(ResponseCodes::SUCCESFUL))),
		m_handlerFactor.createMenuRequestHandler());
}

RequestResult LoginRequestHandler::_signup(const RequestInfo& requestInfo) const
{
	SignupRequest signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buffer);

	//Throws an Exception if the signup doesn't work
	this->m_handlerFactor.getLoginManager().signup(signupRequest.username, signupRequest.password, signupRequest.email);

	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(SignupResponse(static_cast<unsigned int>(ResponseCodes::SUCCESFUL))),
		m_handlerFactor.createMenuRequestHandler());
}