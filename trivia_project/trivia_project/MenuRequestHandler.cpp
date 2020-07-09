#include "pch.h"
#include "MenuRequestHandler.h"

//TODO: Make sure things are const

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory) :
	m_handlerFactory(handlerFactory)
{
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	return this->handleAllRequests(requestInfo, *this, this->m_requests);
}

void MenuRequestHandler::reset(LoggedUser user)
{
	this->m_user = user;
}

RequestResult MenuRequestHandler::_signout(const RequestInfo& requestInfo)
{
	//Throws an Exception if the login doesn't work
	this->m_handlerFactory.getLoginManager().logout(this->m_user.username);

	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			LogoutResponse()
		),
		this->m_handlerFactory.createLoginRequestHandler()
	);
}

RequestResult MenuRequestHandler::_getRooms(const RequestInfo& requestInfo)
{
	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			GetRoomResponse(this->m_handlerFactory.getRoomManager().getRooms())
		),
		*this
	);
}

RequestResult MenuRequestHandler::_getPlayersInRoom(const RequestInfo& requestInfo)
{
	GetPlayersInRoomRequest::RoomIdRequest getPlayersInRoomRequest = JsonRequestPacketDeserializer::deserializeRoomIdRequest(requestInfo.buffer);

	return RequestResult(
			JsonResponsePacketSerializer::serializeResponse(
				GetPlayersInRoomResponse(this->m_handlerFactory.getRoomManager().getUsersInRoom(getPlayersInRoomRequest.roomId))
		),
		*this
	);
}

RequestResult MenuRequestHandler::_getUserStats(const RequestInfo& requestInfo)
{
	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			GetUserStatsResponse(this->m_handlerFactory.getStatisticsManager().getUserStats(this->m_user.username))
		),
		*this
	);
}

RequestResult MenuRequestHandler::_getHighScores(const RequestInfo& requestInfo)
{
	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			GetHighScoresResponse(this->m_handlerFactory.getStatisticsManager().getHighScores())
		),
		*this
	);
}

RequestResult MenuRequestHandler::_joinRoom(const RequestInfo& requestInfo)
{
	JoinRoomRequest::RoomIdRequest joinRoomRequest = JsonRequestPacketDeserializer::deserializeRoomIdRequest(requestInfo.buffer);

	this->m_handlerFactory.getRoomManager().getRoom(joinRoomRequest.roomId).addUser(this->m_user);

	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			JoinRoomResponse()
		),
		this->m_handlerFactory.createRoomMemberRequestHandler(
			this->m_user,
			this->m_handlerFactory.getRoomManager().getRoom(joinRoomRequest.roomId)
		)
	);
}

RequestResult MenuRequestHandler::_createRoom(const RequestInfo& requestInfo)
{
	CreateRoomRequest createRoomRequest = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(requestInfo.buffer);

	this->m_handlerFactory.getRoomManager().createRoom(createRoomRequest.room);

	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			CreateRoomResponse()
		),
		this->m_handlerFactory.createRoomAdminRequestHandler(
			this->m_user,
			this->m_handlerFactory.getRoomManager().getRoom(createRoomRequest.room.getId())
		)
	);
}

const map<Codes, MenuRequestHandler::requests_func_t> MenuRequestHandler::m_requests = {
	{ Codes::LOGOUT, &MenuRequestHandler::_signout },
	{ Codes::GET_ROOM, &MenuRequestHandler::_getRooms },
	{ Codes::GET_PLAYERS_IN_ROOM, &MenuRequestHandler::_getPlayersInRoom },
	{ Codes::USER_STATS, &MenuRequestHandler::_getUserStats },
	{ Codes::HIGH_SCORES, &MenuRequestHandler::_getHighScores },
	{ Codes::JOIN_ROOM, &MenuRequestHandler::_joinRoom },
	{ Codes::CREATE_ROOM, &MenuRequestHandler::_createRoom }
};