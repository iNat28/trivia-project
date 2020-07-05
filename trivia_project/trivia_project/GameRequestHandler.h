#pragma once
#include "LoggedUserRequestHandler.h"
#include "RequestHandlerFactory.h"

class GameRequestHandler :
	public LoggedUserRequestHandler
{
public:
	GameRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user);

	virtual RequestResult handleRequest(const RequestInfo& requestInfo) const override;
private:
	RequestHandlerFactory& m_handlerFactory;
};

