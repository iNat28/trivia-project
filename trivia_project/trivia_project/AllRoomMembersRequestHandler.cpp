#include "pch.h"
#include "AllRoomMembersRequestHandler.h"

AllRoomMembersRequestHandler::AllRoomMembersRequestHandler(RequestHandlerFactory& handlerFactor, LoggedUser user, Room& room) : 
	IRequestHandler(handlerFactor), m_user(user), m_room(room)
{
}

RequestResult AllRoomMembersRequestHandler::_getRoomStateNoHandler(const RequestInfo& requestInfo) const
{
	IRequestHandlerPtr handler;
	ResponseCodes responseCode;

	if (this->m_room.isClosed())
	{
		handler = this->createMenuRequestHandler();
		responseCode = ResponseCodes::ROOM_CLOSED;
	}
	else if (this->m_room.didGameStart())
	{
		handler = this->createMenuRequestHandler();
		responseCode = ResponseCodes::ROOM_CLOSED;
	}
	else
	{
		handler = nullptr;
		responseCode = ResponseCodes::ROOM_OPEN;
	}

	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			GetRoomStateResponse(
				static_cast<unsigned int>(responseCode),
				this->m_room.getRoomState()
			)
		),
		handler
	);
}

std::shared_ptr<MenuRequestHandler> AllRoomMembersRequestHandler::createMenuRequestHandler() const
{
	return this->m_handlerFactory.createRequestHandler(MenuRequestHandler(this->m_handlerFactory, this->m_user));
}
