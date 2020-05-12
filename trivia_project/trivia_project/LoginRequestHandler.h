#pragma once
#include "pch.h"
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "IDatabase.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	//c'tor
	LoginRequestHandler(IDatabasePtr database);

	virtual bool isRequestRelevant(const RequestInfo& requestInfo) override;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) override;

private:
	RequestHandlerFactory m_handlerFactor;
	
	RequestResult _login(const RequestInfo& requestInfo);
	RequestResult _signup(const RequestInfo& requestInfo);

	//TODO: Add map for request codes and functions
	//using handler_func_t = Buffer(LoginRequestHandler::*)(void);
	//std::unordered_map<RequestCodes, 
};