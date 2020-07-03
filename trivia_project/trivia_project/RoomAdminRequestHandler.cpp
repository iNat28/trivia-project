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

RequestResult RoomAdminRequestHandler::_closeRoom(const RequestInfo& requestInfo) const
{
	this->m_handlerFactory.getRoomManager().closeRoom(this->m_room);

	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			CloseRoomResponse(static_cast<unsigned int>(ResponseCodes::SUCCESFUL))
		),
		this->createMenuRequestHandler()
	);
}

RequestResult RoomAdminRequestHandler::_startGame(const RequestInfo& requestInfo) const
{
	return RequestResult();
}

RequestResult RoomAdminRequestHandler::_getRoomState(const RequestInfo& requestInfo) const
{
	RequestResult requestResult = this->_getRoomStateNoHandler(requestInfo);

	if (requestResult.newHandler == nullptr)
	{
		requestResult.newHandler = this->m_handlerFactory.createRequestHandler(*this);
	}

	return requestResult;
}

const map<Codes, RoomAdminRequestHandler::requests_func_t> RoomAdminRequestHandler::m_requests = {
	{ Codes::CLOSE_ROOM, &RoomAdminRequestHandler::_closeRoom },
	{ Codes::START_GAME, &RoomAdminRequestHandler::_startGame },
	{ Codes::GET_ROOM_STATE, &RoomAdminRequestHandler::_getRoomState }
};