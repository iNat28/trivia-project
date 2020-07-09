#pragma once
#include "AllRoomMembersRequestHandler.h"
#include "RequestHandlerFactory.h"

class RoomMemberRequestHandler :
	public AllRoomMembersRequestHandler
{
public:
	RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user, Room& room);

	virtual RequestResult handleRequest(const RequestInfo& requestInfo) override;
private:
	using requests_func_t = RequestResult(RoomMemberRequestHandler::*)(const RequestInfo&) const;
	static const map<Codes, RoomMemberRequestHandler::requests_func_t> m_requests;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult _leaveRoom(const RequestInfo& requestInfo) const;
	RequestResult _getRoomState(const RequestInfo& requestInfo) const;
};