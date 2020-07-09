#pragma once
#include "AllRoomMembersRequestHandler.h"
#include "RequestHandlerFactory.h"

class RoomAdminRequestHandler :
	public AllRoomMembersRequestHandler
{
public:
	RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory);

	virtual RequestResult handleRequest(const RequestInfo& requestInfo) override;
private:
	using requests_func_t = RequestResult(RoomAdminRequestHandler::*)(const RequestInfo&);
	static const map<Codes, RoomAdminRequestHandler::requests_func_t> m_requests;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult _closeRoom(const RequestInfo& requestInfo);
	RequestResult _startGame(const RequestInfo& requestInfo);
	RequestResult _getRoomState(const RequestInfo& requestInfo);
};