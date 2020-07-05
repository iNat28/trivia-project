#pragma once
#include "IRequestHandler.h"

class AllRoomMembersRequestHandler :
	public IRequestHandler
{
protected:
	AllRoomMembersRequestHandler(LoggedUser user, Room& room);
	LoggedUser m_user;
	Room& m_room;
	
	RequestResult _getRoomStateNoHandler(const RequestInfo& requestInfo) const;
	//TODO: Maybe change MenuRequestHandler and this class to inherit from UserRequestHandler (has user attribute)
};

