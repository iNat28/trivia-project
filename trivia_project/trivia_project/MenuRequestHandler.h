#pragma once
#include "pch.h"
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "Constants.h"
#include "LoggedUser.h"
#include "IDatabase.h"
#include "LoginRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

class LoginRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory& handlerFactor, LoggedUser user);

	virtual RequestResult handleRequest(const RequestInfo& requestInfo) const override;
private:
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
};
