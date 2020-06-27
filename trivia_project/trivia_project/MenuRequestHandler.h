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
	using requests_func_t = RequestResult(MenuRequestHandler::*)(const RequestInfo&)const;
	static const map<Codes, MenuRequestHandler::requests_func_t> m_requests;

	RequestResult _signout(const RequestInfo& requestInfo) const;
	RequestResult _getRooms(const RequestInfo& requestInfo) const;
	RequestResult _getPlayersInRoom(const RequestInfo& requestInfo) const;
	RequestResult _getUserStats(const RequestInfo& requestInfo) const;
	RequestResult _getHighScores(const RequestInfo& requestInfo) const;
	RequestResult _joinRoom(const RequestInfo& requestInfo) const;
	RequestResult _createRoom(const RequestInfo& requestInfo) const;
	RequestResult _closeRoom(const RequestInfo& requestInfo) const;
};
