#pragma once
#include "pch.h"
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "Constants.h"
#include "LoggedUser.h"
#include "IDatabase.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory& handlerFactor);

	virtual RequestResult handleRequest(const RequestInfo& requestInfo) const override;
private:
	RequestHandlerFactory& m_handlerFactor;
	LoggedUser m_user;

	RequestResult _signout(const RequestInfo& requestInfo) const;
	RequestResult _getRooms(const RequestInfo& requestInfo) const;
	RequestResult _getPlayersInRoom(const RequestInfo& requestInfo) const;
	//TODO: Create the rest
	RequestResult _getStatistics(const RequestInfo& requestInfo) const;
	RequestResult _joinRoom(const RequestInfo& requestInfo) const;
	RequestResult _createRoom(const RequestInfo& requestInfo) const;
};
