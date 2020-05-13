#include "pch.h"
#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabasePtr database) : 
	m_loginManager(database), m_database(database)
{
}

LoginRequestHandler RequestHandlerFactory::createLoginRequestHandler()
{
	return LoginRequestHandler(this->m_database);
}

MenuRequestHandler RequestHandlerFactory::createMenuRequestHandler()
{
	return MenuRequestHandler(this->m_database);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}



LoginRequestHandler::LoginRequestHandler(IDatabasePtr database) :
	m_handlerFactor(database)
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
	IRequestHandlerPtr handler;

	try {
		LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
		handler = std::make_shared<MenuRequestHandler>(m_handlerFactor.createMenuRequestHandler());
		//TODO:	Check if login was valid
		//		If not:
		//handler = std::make_shared<LoginRequestHandler>(m_handlerFactor.createLoginRequestHandler());
	}
	catch (...)
	{
		unsigned int response = 0;
	}

	return RequestResult(JsonResponsePacketSerializer::serializeResponse(LoginResponse{ response }), handler);
}

RequestResult LoginRequestHandler::_signup(const RequestInfo& requestInfo)
{
	unsigned int response = 1;
	IRequestHandlerPtr handler;

	try {
		SignupRequest signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buffer);
		handler = std::make_shared<MenuRequestHandler>(m_handlerFactor.createMenuRequestHandler());
		//TODO:	Check if signup was valid
		//		If not:
		//handler = std::make_shared<LoginRequestHandler>(m_handlerFactor.createLoginRequestHandler());
	}
	catch (...)
	{
		unsigned int response = 0;
	}

	return RequestResult(JsonResponsePacketSerializer::serializeResponse(SignupResponse{ response }), handler);
}



MenuRequestHandler::MenuRequestHandler(IDatabasePtr database) :
	m_handlerFactor(database)
{
}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
	return true;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	return RequestResult();
}