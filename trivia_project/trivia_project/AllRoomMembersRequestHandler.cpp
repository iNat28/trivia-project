#include "pch.h"
#include "AllRoomMembersRequestHandler.h"

void AllRoomMembersRequestHandler::reset(LoggedUser user, Room& room)
{
	this->m_user = user;
	this->m_room = &room;
}

AllRoomMembersRequestHandler::AllRoomMembersRequestHandler() :
	m_room(nullptr)
{
}

//getting room state of room
Buffer AllRoomMembersRequestHandler::_getRoomStateNoHandler(const RequestInfo& requestInfo)
{
	return JsonResponsePacketSerializer::serializeResponse(
		GetRoomStateResponse(
			this->m_room->getRoomStatus(),
			this->m_room->getAllUsers()
		)
	);
}