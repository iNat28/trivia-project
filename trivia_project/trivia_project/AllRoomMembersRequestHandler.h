#pragma once
#include "IRequestHandler.h"
#include "MenuRequestHandler.h"

class MenuRequestHandler;

class AllRoomMembersRequestHandler :
	public IRequestHandler
{
public:
	AllRoomMembersRequestHandler(RequestHandlerFactory& handlerFactor, LoggedUser user, Room& room);
protected:
	LoggedUser m_user;
	Room& m_room;

	RequestResult _getRoomStateNoHandler(const RequestInfo& requestInfo) const;
	//TODO: Maybe change MenuRequestHandler and this class to inherit from UserRequestHandler (has user attribute)
	std::shared_ptr<MenuRequestHandler> createMenuRequestHandler() const;
};

