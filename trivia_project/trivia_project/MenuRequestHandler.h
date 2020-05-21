#pragma once
#include "pch.h"
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "IDatabase.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory& handlerFactor);

	virtual bool isRequestRelevant(const RequestInfo& requestInfo) const override;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) const override;

private:
	RequestHandlerFactory& m_handlerFactor;
};
