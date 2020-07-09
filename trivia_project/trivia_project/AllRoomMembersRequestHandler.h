#pragma once
#include "LoggedUserRequestHandler.h"

class AllRoomMembersRequestHandler :
	public LoggedUserRequestHandler
{
public:
	void reset(LoggedUser user, Room& room);
protected:
	AllRoomMembersRequestHandler();

	Room* m_room;

	Buffer _getRoomStateNoHandler(const RequestInfo& requestInfo);
};

