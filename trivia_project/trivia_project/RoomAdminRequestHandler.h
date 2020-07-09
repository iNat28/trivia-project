#pragma once
#include "AllRoomMembersRequestHandler.h"
#include "RequestHandlerFactory.h"

class RoomAdminRequestHandler :
	public AllRoomMembersRequestHandler
{
public:
	RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user, Room& room);

	virtual RequestResult handleRequest(const RequestInfo& requestInfo) override;
private:
	using requests_func_t = RequestResult(RoomAdminRequestHandler::*)(const RequestInfo&) const;
	static const map<Codes, RoomAdminRequestHandler::requests_func_t> m_requests;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult _closeRoom(const RequestInfo& requestInfo) const;
	RequestResult _startGame(const RequestInfo& requestInfo) const;
	RequestResult _getRoomState(const RequestInfo& requestInfo) const;
};