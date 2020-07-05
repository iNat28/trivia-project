#include "pch.h"
#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user, Room& room) :
	AllRoomMembersRequestHandler(user, room), m_handlerFactory(handlerFactory)
{
}

RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& requestInfo) const
{
	RoomMemberRequestHandler::requests_func_t handler = nullptr;

	//If at any point the requests don't work, an exception will be thrown, 
	//and it will be put into an error response
	try {
		handler = m_requests.at(requestInfo.requestId);
		return (this->*handler)(requestInfo);
	}
	catch (const std::exception & e)
	{
		return RequestResult(
			JsonResponsePacketSerializer::serializeResponse(ErrorResponse(e.what())),
			this->m_handlerFactory.createRoomMemberRequestHandler(this->m_user, this->m_room)
		);
	}
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
	RequestResult requestResult = this->_getRoomStateNoHandler(requestInfo);

	switch (this->m_room.getRoomStatus())
	{
	case RoomStatus::OPEN:
		requestResult.newHandler = this->m_handlerFactory.createRoomMemberRequestHandler(this->m_user, this->m_room);
		break;
	case RoomStatus::CLOSED:
		requestResult.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
		break;
	case RoomStatus::GAME_STARTED:
		//TODO
		//handler = this->m_handlerFactory.createGameRequestHandler();
		break;
	}

	return requestResult;
}

const map<Codes, RoomMemberRequestHandler::requests_func_t> RoomMemberRequestHandler::m_requests = {
	{ Codes::LEAVE_ROOM, &RoomMemberRequestHandler::_leaveRoom },
	{ Codes::GET_ROOM_STATE, &RoomMemberRequestHandler::_getRoomState }
};