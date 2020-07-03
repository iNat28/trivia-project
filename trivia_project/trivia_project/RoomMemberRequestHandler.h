#pragma once
#include "AllRoomMembersRequestHandler.h"

class RoomMemberRequestHandler :
	public AllRoomMembersRequestHandler
{
public:
	using AllRoomMembersRequestHandler::AllRoomMembersRequestHandler;

	virtual RequestResult handleRequest(const RequestInfo& requestInfo) const override;
private:
	using requests_func_t = RequestResult(RoomMemberRequestHandler::*)(const RequestInfo&) const;
	static const map<Codes, RoomMemberRequestHandler::requests_func_t> m_requests;

	RequestResult _leaveRoom(const RequestInfo& requestInfo) const;
	RequestResult _getRoomState(const RequestInfo& requestInfo) const;
};