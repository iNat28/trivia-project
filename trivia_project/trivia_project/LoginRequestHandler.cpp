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
	std::cout << "Username: " << loginRequest.username << " Password: " << loginRequest.password << std::endl;
	return RequestResult();
}
