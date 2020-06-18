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
	MenuRequestHandler(RequestHandlerFactory& handlerFactor, LoggedUser user);

	virtual RequestResult handleRequest(const RequestInfo& requestInfo) const override;
private:
	RequestHandlerFactory& m_handlerFactor;
	LoggedUser m_user;
	using requests_func_t = Buffer(MenuRequestHandler::*)(const RequestInfo&)const;
	static const map<Codes, MenuRequestHandler::requests_func_t> m_requests;

	Buffer _signout(const RequestInfo& requestInfo) const;
	Buffer _getRooms(const RequestInfo& requestInfo) const;
	Buffer _getPlayersInRoom(const RequestInfo& requestInfo) const;
	Buffer _getStatistics(const RequestInfo& requestInfo) const;
	Buffer _joinRoom(const RequestInfo& requestInfo) const;
	Buffer _createRoom(const RequestInfo& requestInfo) const;
};
