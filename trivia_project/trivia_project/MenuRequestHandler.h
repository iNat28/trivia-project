#pragma once
#include "pch.h"
#include "RequestHandlerFactory.h"
#include "LoggedUserRequestHandler.h"
#include "Constants.h"
#include "LoggedUser.h"

class RequestHandlerFactory;

class MenuRequestHandler : public LoggedUserRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory& handlerFactory);

	virtual RequestResult handleRequest(const RequestInfo& requestInfo) override;

	void reset(LoggedUser user);
private:
	RequestHandlerFactory& m_handlerFactory;
	using requests_func_t = RequestResult(MenuRequestHandler::*)(const RequestInfo&);
	static const map<Codes, MenuRequestHandler::requests_func_t> m_requests;

	RequestResult _signout(const RequestInfo& requestInfo);
	RequestResult _getRooms(const RequestInfo& requestInfo);
	RequestResult _getPlayersInRoom(const RequestInfo& requestInfo);
	RequestResult _getUserStats(const RequestInfo& requestInfo);
	RequestResult _getHighScores(const RequestInfo& requestInfo);
	RequestResult _joinRoom(const RequestInfo& requestInfo);
	RequestResult _createRoom(const RequestInfo& requestInfo);
};
