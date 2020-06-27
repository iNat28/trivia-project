#include "pch.h"
#include "MenuRequestHandler.h"

//TODO: Make sure things are const

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactor, LoggedUser user) :
	m_handlerFactor(handlerFactor), m_user(user)
{
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& requestInfo) const
{
	Buffer requestResultBuffer;
	MenuRequestHandler::requests_func_t handler = nullptr;

	//If at any point the requests don't work, an exception will be thrown, 
	//and it will be put into an error response
	try {
		handler = m_requests.at(requestInfo.requestId);
		return (this->*handler)(requestInfo);
	}
	catch (const std::exception& e)
	{
		return RequestResult(
			JsonResponsePacketSerializer::serializeResponse(ErrorResponse(e.what())),
			this->m_handlerFactor.createMenuRequestHandler(this->m_user)
		);
	}
}

RequestResult MenuRequestHandler::_signout(const RequestInfo& requestInfo) const
{
	//Throws an Exception if the login doesn't work
	this->m_handlerFactor.getLoginManager().logout(this->m_user.username);

	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			LogoutResponse(static_cast<unsigned int>(ResponseCodes::SUCCESFUL))
		),
		this->m_handlerFactor.createLoginRequestHandler()
	);
}

RequestResult MenuRequestHandler::_getRooms(const RequestInfo& requestInfo) const
{
	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			GetRoomResponse(
				static_cast<unsigned int>(ResponseCodes::SUCCESFUL), 
				this->m_handlerFactor.getRoomManager().getRooms()
			)
		),
		this->m_handlerFactor.createMenuRequestHandler(this->m_user)
	);
}

RequestResult MenuRequestHandler::_getPlayersInRoom(const RequestInfo& requestInfo) const
{
	GetPlayersInRoomRequest::RoomIdRequest getPlayersInRoomRequest = JsonRequestPacketDeserializer::deserializeRoomIdRequest(requestInfo.buffer);

	return RequestResult(
			JsonResponsePacketSerializer::serializeResponse(
				GetPlayersInRoomResponse(this->m_handlerFactor.getRoomManager().getUsersInRoom(getPlayersInRoomRequest.roomId))
		),
		this->m_handlerFactor.createMenuRequestHandler(this->m_user)
	);
}

RequestResult MenuRequestHandler::_getUserStats(const RequestInfo& requestInfo) const
{
	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			GetUserStatsResponse(static_cast<unsigned int>(ResponseCodes::SUCCESFUL),
				this->m_handlerFactor.getStatisticsManager().getUserStats(this->m_user.username)
			)
		),
		this->m_handlerFactor.createMenuRequestHandler(this->m_user)
	);
}

RequestResult MenuRequestHandler::_getHighScores(const RequestInfo& requestInfo) const
{
	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			GetHighScoresResponse(static_cast<unsigned int>(ResponseCodes::SUCCESFUL),
				this->m_handlerFactor.getStatisticsManager().getHighScores()
			)
		),
		this->m_handlerFactor.createMenuRequestHandler(this->m_user)
	);
}

RequestResult MenuRequestHandler::_joinRoom(const RequestInfo& requestInfo) const
{
	JoinRoomRequest::RoomIdRequest joinRoomRequest = JsonRequestPacketDeserializer::deserializeRoomIdRequest(requestInfo.buffer);

	this->m_handlerFactor.getRoomManager().getRoom(joinRoomRequest.roomId).addUser(this->m_user);

	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			JoinRoomResponse(static_cast<unsigned int>(ResponseCodes::SUCCESFUL))
		),
		this->m_handlerFactor.createMenuRequestHandler(this->m_user)
	);
}

RequestResult MenuRequestHandler::_createRoom(const RequestInfo& requestInfo) const
{
	CreateRoomRequest createRoomRequest = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(requestInfo.buffer);

	this->m_handlerFactor.getRoomManager().createRoom(createRoomRequest.roomData, createRoomRequest.adminUsername);

	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			CreateRoomResponse(static_cast<unsigned int>(ResponseCodes::SUCCESFUL))
		),
		this->m_handlerFactor.createMenuRequestHandler(this->m_user)
	);
}

RequestResult MenuRequestHandler::_closeRoom(const RequestInfo& requestInfo) const
{
	CloseRoomRequest::RoomIdRequest closeRoomRequest = JsonRequestPacketDeserializer::deserializeRoomIdRequest(requestInfo.buffer);

	this->m_handlerFactor.getRoomManager().deleteRoom(closeRoomRequest.roomId);

	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			CloseRoomResponse(static_cast<unsigned int>(ResponseCodes::SUCCESFUL))
		),
		this->m_handlerFactor.createMenuRequestHandler(this->m_user)
	);
}

const map<Codes, MenuRequestHandler::requests_func_t> MenuRequestHandler::m_requests = {
	{ Codes::LOGOUT, &MenuRequestHandler::_signout },
	{ Codes::GET_ROOM, &MenuRequestHandler::_getRooms },
	{ Codes::GET_PLAYERS_IN_ROOM, &MenuRequestHandler::_getPlayersInRoom },
	{ Codes::USER_STATS, &MenuRequestHandler::_getUserStats },
	{ Codes::HIGH_SCORES, &MenuRequestHandler::_getHighScores },
	{ Codes::JOIN_ROOM, &MenuRequestHandler::_joinRoom },
	{ Codes::CREATE_ROOM, &MenuRequestHandler::_createRoom },
	{ Codes::CLOSE_ROOM, &MenuRequestHandler::_closeRoom }
};