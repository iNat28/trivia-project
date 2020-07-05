#include "pch.h"
#include "AllRoomMembersRequestHandler.h"

AllRoomMembersRequestHandler::AllRoomMembersRequestHandler(LoggedUser user, Room& room) : 
	m_user(user), m_room(room)
{
}

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