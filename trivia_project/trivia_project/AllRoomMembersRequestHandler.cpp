#include "pch.h"
#include "AllRoomMembersRequestHandler.h"

AllRoomMembersRequestHandler::AllRoomMembersRequestHandler(LoggedUser user, Room& room) : 
	LoggedUserRequestHandler(user), m_room(room)
{
}
//getting room state of room
RequestResult AllRoomMembersRequestHandler::_getRoomStateNoHandler(const RequestInfo& requestInfo) const
{
	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			GetRoomStateResponse(
				this->m_room.getRoomStatus(),
				this->m_room.getAllUsers()
			)
		),
		nullptr
	);
}