#pragma once
#include "AllRoomMembersRequestHandler.h"
#include "MenuRequestHandler.h"

class RoomAdminRequestHandler :
	public AllRoomMembersRequestHandler
{
public:
	using AllRoomMembersRequestHandler::AllRoomMembersRequestHandler;

	virtual RequestResult handleRequest(const RequestInfo& requestInfo) const;
private:
	using requests_func_t = RequestResult(RoomAdminRequestHandler::*)(const RequestInfo&) const;
	static const map<Codes, RoomAdminRequestHandler::requests_func_t> m_requests;

	RequestResult _closeRoom(const RequestInfo& requestInfo) const;
	RequestResult _startGame(const RequestInfo& requestInfo) const;
};

