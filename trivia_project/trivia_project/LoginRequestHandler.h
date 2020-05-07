#pragma once
#include "pch.h"
#include "IRequestHandler.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	//c'tor
	LoginRequestHandler();

	virtual bool isRequestRelevant(const RequestInfo& requestInfo);
	virtual RequestResult handleRequest(const RequestInfo& requestInfo);
};