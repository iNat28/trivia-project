#pragma once
#include "pch.h"
#include "IRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	//c'tor
	LoginRequestHandler();

	virtual bool isRequestRelevant(const RequestInfo& requestInfo);
	virtual RequestResult handleRequest(const RequestInfo& requestInfo);

	Buffer handleLoginRequest(const Buffer& buffer);
	Buffer handleSignupRequest(const Buffer& buffer);

	//TODO: Add map for request codes and functions
	//using handler_func_t = Buffer(LoginRequestHandler::*)(void);
	//std::unordered_map<RequestCodes, 
};