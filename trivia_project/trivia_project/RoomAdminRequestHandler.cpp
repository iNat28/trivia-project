#include "pch.h"
#include "RoomAdminRequestHandler.h"

RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& requestInfo) const
{
	RoomAdminRequestHandler::requests_func_t handler = nullptr;

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
			this->m_handlerFactory.createRequestHandler(*this)
		);
	}
}

RequestResult RoomAdminRequestHandler::_leaveRoom(const RequestInfo& requestInfo) const
{
	this->m_room.removeUser(this->m_user);

	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			LeaveRoomResponse(static_cast<unsigned int>(ResponseCodes::SUCCESFUL))
		),
		this->m_handlerFactory.createRequestHandler(MenuRequestHandler(this->m_handlerFactory, this->m_user))
	);
}

const map<Codes, RoomAdminRequestHandler::requests_func_t> RoomAdminRequestHandler::m_requests = {
	{ Codes::LEAVE_ROOM, &RoomAdminRequestHandler::_leaveRoom },
	{ Codes::GET_ROOM_STATE, &AllRoomMembersRequestHandler::_getRoomState }
};