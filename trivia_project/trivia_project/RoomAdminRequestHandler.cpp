#include "pch.h"
#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user, Room& room) :
	AllRoomMembersRequestHandler(user, room), m_handlerFactory(handlerFactory)
{
}

RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	return this->handleAllRequests(requestInfo, *this, this->m_requests);
}

RequestResult RoomAdminRequestHandler::_closeRoom(const RequestInfo& requestInfo) const
{
	this->m_handlerFactory.getRoomManager().closeRoom(this->m_room);

	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			CloseRoomResponse()
		),
		this->m_handlerFactory.createMenuRequestHandler(this->m_user)
	);
}

RequestResult RoomAdminRequestHandler::_startGame(const RequestInfo& requestInfo) const
{
	this->m_room.setRoomStatus(RoomStatus::GAME_STARTED);

	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			StartGameResponse()
		),
		this->m_handlerFactory.createGameRequestHandler(
			this->m_user,
			this->m_handlerFactory.getGameManager().createGame(
				this->m_room,
				this->m_handlerFactory.getGameManager().getQuestions(this->m_room.getQuestionsCount())
			)
		)
	);
}

RequestResult RoomAdminRequestHandler::_getRoomState(const RequestInfo& requestInfo) const
{
	return RequestResult(
		this->_getRoomStateNoHandler(requestInfo),
		this->m_handlerFactory.createRoomAdminRequestHandler(this->m_user, this->m_room)
	);
}

const map<Codes, RoomAdminRequestHandler::requests_func_t> RoomAdminRequestHandler::m_requests = {
	{ Codes::CLOSE_ROOM, &RoomAdminRequestHandler::_closeRoom },
	{ Codes::START_GAME, &RoomAdminRequestHandler::_startGame },
	{ Codes::GET_ROOM_STATE, &RoomAdminRequestHandler::_getRoomState }
};