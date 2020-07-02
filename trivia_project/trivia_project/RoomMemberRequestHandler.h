#pragma once
#include "AllRoomMembersRequestHandler.h"
#include "MenuRequestHandler.h"

class RoomMemberRequestHandler :
	public AllRoomMembersRequestHandler
{
public:
	using AllRoomMembersRequestHandler::AllRoomMembersRequestHandler;

	virtual RequestResult handleRequest(const RequestInfo& requestInfo) const;
private:
	using requests_func_t = RequestResult(RoomMemberRequestHandler::*)(const RequestInfo&) const;
	static const map<Codes, RoomMemberRequestHandler::requests_func_t> m_requests;

	RequestResult _leaveRoom(const RequestInfo& requestInfo) const;
};

