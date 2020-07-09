#include "pch.h"
#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user, Room& room) :
	AllRoomMembersRequestHandler(user, room), m_handlerFactory(handlerFactory)
{
}

RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	return this->handleAllRequests(requestInfo, *this, this->m_requests);
}

RequestResult RoomMemberRequestHandler::_leaveRoom(const RequestInfo& requestInfo) const
{
	this->m_room.removeUser(this->m_user);

	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			LeaveRoomResponse()
		),
		this->m_handlerFactory.createMenuRequestHandler(this->m_user)
	);
}

RequestResult RoomMemberRequestHandler::_getRoomState(const RequestInfo& requestInfo) const
{
	Buffer resultBuffer = this->_getRoomStateNoHandler(requestInfo);

	switch (this->m_room.getRoomStatus())
	{
	case RoomStatus::OPEN:
		return RequestResult(
			resultBuffer,
			this->m_handlerFactory.createRoomMemberRequestHandler(this->m_user, this->m_room)
		);
	case RoomStatus::CLOSED:
		return RequestResult(
			resultBuffer,
			this->m_handlerFactory.createRoomMemberRequestHandler(this->m_user, this->m_room)
		);
	case RoomStatus::GAME_STARTED:
		return RequestResult(
			resultBuffer,
			this->m_handlerFactory.createGameRequestHandler(
				this->m_user,
				this->m_handlerFactory.getGameManager().getGame(this->m_room)
			)
		);
	}

	throw Exception("Room status not found!");
}

const map<Codes, RoomMemberRequestHandler::requests_func_t> RoomMemberRequestHandler::m_requests = {
	{ Codes::LEAVE_ROOM, &RoomMemberRequestHandler::_leaveRoom },
	{ Codes::GET_ROOM_STATE, &RoomMemberRequestHandler::_getRoomState }
};