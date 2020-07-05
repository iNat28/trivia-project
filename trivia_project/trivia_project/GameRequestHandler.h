#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class GameRequestHandler :
	public IRequestHandler
{
public:
	GameRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user);

	virtual RequestResult handleRequest(const RequestInfo& requestInfo) const override;
private:
	RequestHandlerFactory& m_handlerFactory;
	LoggedUser& m_user;
};

