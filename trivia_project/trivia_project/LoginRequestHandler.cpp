#include "pch.h"
#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactor) :
	m_handlerFactor(handlerFactor)
{
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo) const
{
	LoginRequestHandler::requests_func_t handler = nullptr;

	//If at any point the requests don't work, an exception will be thrown, 
	//and it will be put into an error response
	try {
		handler = m_requests.at(requestInfo.requestId);
		return (this->*handler)(requestInfo);
	}
	//Login manager exception caught
	catch (const Exception & e)
	{
		return RequestResult(
			JsonResponsePacketSerializer::serializeResponse(ErrorResponse(e.what())),
			m_handlerFactor.createLoginRequestHandler()
		);
	}
	//Other exception caught (probably because of the json)
	catch (const std::exception & e)
	{
		return RequestResult(
			JsonResponsePacketSerializer::serializeResponse(ErrorResponse(e.what())),
			nullptr
		);
	}
}

RequestResult LoginRequestHandler::_login(const RequestInfo& requestInfo) const
{
	LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
	
	//Throws an Exception if the login doesn't work
	this->m_handlerFactor.getLoginManager().login(loginRequest.username, loginRequest.password);

	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			LoginResponse(static_cast<unsigned int>(ResponseCodes::SUCCESFUL))
		),
		m_handlerFactor.createMenuRequestHandler(loginRequest.username)
	);
}

RequestResult LoginRequestHandler::_signup(const RequestInfo& requestInfo) const
{
	SignupRequest signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buffer);

	//Throws an Exception if the signup doesn't work
	this->m_handlerFactor.getLoginManager().signup(signupRequest.username, signupRequest.password, signupRequest.email);

	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			SignupResponse(static_cast<unsigned int>(ResponseCodes::SUCCESFUL))
		),
		m_handlerFactor.createMenuRequestHandler(signupRequest.username)
	);
}

const map<Codes, LoginRequestHandler::requests_func_t> LoginRequestHandler::m_requests = {
	{ Codes::LOGIN, &LoginRequestHandler::_login },
	{ Codes::SIGNUP, &LoginRequestHandler::_signup }
};