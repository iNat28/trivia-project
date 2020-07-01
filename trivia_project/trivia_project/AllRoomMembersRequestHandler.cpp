#include "pch.h"
#include "AllRoomMembersRequestHandler.h"

AllRoomMembersRequestHandler::AllRoomMembersRequestHandler(RequestHandlerFactory& handlerFactor, LoggedUser user, Room& room) : 
	IRequestHandler(handlerFactor), m_user(user), m_room(room)
{
}

RequestResult AllRoomMembersRequestHandler::_getRoomState(const RequestInfo& requestInfo) const
{
	return RequestResult();
}
