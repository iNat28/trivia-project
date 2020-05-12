#include "pch.h"
#include "MenuRequestHandler.h"

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
