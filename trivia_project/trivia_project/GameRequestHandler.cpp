#include "pch.h"
#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user) : 
	m_handlerFactory(handlerFactory), m_user(user)
{
}

RequestResult GameRequestHandler::handleRequest(const RequestInfo& requestInfo) const
{
	return RequestResult();
}
