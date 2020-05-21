#include "pch.h"
#include "MenuRequestHandler.h"


MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactor) :
	m_handlerFactor(handlerFactor)
{
}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	return true;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& requestInfo) const
{
	return RequestResult();
}