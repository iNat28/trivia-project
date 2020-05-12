#pragma once
#include "pch.h"
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "IDatabase.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(IDatabasePtr database);

	virtual bool isRequestRelevant(const RequestInfo& requestInfo) override;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) override;

private:
	RequestHandlerFactory m_handlerFactor;
};

