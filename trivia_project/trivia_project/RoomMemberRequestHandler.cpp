#include "pch.h"
#include "RoomMemberRequestHandler.h"

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
			this->m_handlerFactory.createRequestHandler(*this)
		);
	}
}

RequestResult RoomMemberRequestHandler::_closeRoom(const RequestInfo& requestInfo) const
{
	return RequestResult();
}

RequestResult RoomMemberRequestHandler::_startGame(const RequestInfo& requestInfo) const
{
	return RequestResult();
}

const map<Codes, RoomMemberRequestHandler::requests_func_t> RoomMemberRequestHandler::m_requests = {
	{ Codes::CLOSE_ROOM, &RoomMemberRequestHandler::_closeRoom },
	{ Codes::START_GAME, &RoomMemberRequestHandler::_startGame },
	{ Codes::GET_ROOM_STATE, &RoomMemberRequestHandler::_getRoomState }
};