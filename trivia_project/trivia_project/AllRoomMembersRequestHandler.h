#pragma once
#include "LoggedUserRequestHandler.h"

class AllRoomMembersRequestHandler :
	public LoggedUserRequestHandler
{
protected:
	AllRoomMembersRequestHandler(LoggedUser user, Room& room);
	Room& m_room;
	
	RequestResult _getRoomStateNoHandler(const RequestInfo& requestInfo) const;
};

