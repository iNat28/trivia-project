#include "pch.h"
#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler()
{
}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
	//TODO
	return false;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
	return RequestResult();
}
