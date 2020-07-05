#include "pch.h"
#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user) : 
	LoggedUserRequestHandler(user), m_handlerFactory(handlerFactory)
{
}

RequestResult GameRequestHandler::handleRequest(const RequestInfo& requestInfo) const
{
	return RequestResult();
}
