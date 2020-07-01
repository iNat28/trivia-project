#pragma once
#include "IRequestHandler.h"

class RequestHandlerFactory;

class AllRoomMembersRequestHandler :
	public IRequestHandler
{
public:
	AllRoomMembersRequestHandler(RequestHandlerFactory& handlerFactor, LoggedUser user, Room& room);

	LoggedUser m_user;
	Room& m_room;

	RequestResult _getRoomState(const RequestInfo& requestInfo) const;
};

