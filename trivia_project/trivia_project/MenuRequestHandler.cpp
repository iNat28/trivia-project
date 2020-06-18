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
		requestResultBuffer = (this->*handler)(requestInfo);
	}
	catch (const std::exception& e)
	{
		return RequestResult(
			JsonResponsePacketSerializer::serializeResponse(ErrorResponse(e.what())),
			nullptr
		);
	}

	return RequestResult(requestResultBuffer, this->m_handlerFactor.createMenuRequestHandler(this->m_user));
}

Buffer MenuRequestHandler::_signout(const RequestInfo& requestInfo) const
{
	//Throws an Exception if the login doesn't work
	this->m_handlerFactor.getLoginManager().logout(this->m_user.username);

	return JsonResponsePacketSerializer::serializeResponse(
		LogoutResponse(static_cast<unsigned int>(ResponseCodes::SUCCESFUL))
	);
}

Buffer MenuRequestHandler::_getRooms(const RequestInfo& requestInfo) const
{
	return JsonResponsePacketSerializer::serializeResponse(
		GetRoomResponse(
			static_cast<unsigned int>(ResponseCodes::SUCCESFUL), 
			this->m_handlerFactor.getRoomManager().getRooms()
		)
	);
}

Buffer MenuRequestHandler::_getPlayersInRoom(const RequestInfo& requestInfo) const
{
	GetPlayersInRoomRequest::RoomIdRequest getPlayersInRoomRequest = JsonRequestPacketDeserializer::deserializeRoomIdRequest(requestInfo.buffer);

	return JsonResponsePacketSerializer::serializeResponse(
			GetPlayersInRoomResponse(this->m_handlerFactor.getRoomManager().getUsersInRoom(getPlayersInRoomRequest.roomId))
	);
}

Buffer MenuRequestHandler::_getStatistics(const RequestInfo& requestInfo) const
{
	return JsonResponsePacketSerializer::serializeResponse(
		GetStatisticsResponse(static_cast<unsigned int>(ResponseCodes::SUCCESFUL),
			this->m_handlerFactor.getStatisticsManager().getStatistics(this->m_user.username)
		)
	);
}

Buffer MenuRequestHandler::_joinRoom(const RequestInfo& requestInfo) const
{
	JoinRoomRequest::RoomIdRequest joinRoomRequest = JsonRequestPacketDeserializer::deserializeRoomIdRequest(requestInfo.buffer);

	this->m_handlerFactor.getRoomManager().getRoom(joinRoomRequest.roomId).addUser(this->m_user);

	return JsonResponsePacketSerializer::serializeResponse(
		JoinRoomResponse(static_cast<unsigned int>(ResponseCodes::SUCCESFUL))
	);
}

Buffer MenuRequestHandler::_createRoom(const RequestInfo& requestInfo) const
{
	CreateRoomRequest createRoomRequest = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(requestInfo.buffer);

	this->m_handlerFactor.getRoomManager().createRoom(this->m_user.username, createRoomRequest.roomData);

	return JsonResponsePacketSerializer::serializeResponse(
		CreateRoomResponse(static_cast<unsigned int>(ResponseCodes::SUCCESFUL))
	);
}

const map<Codes, MenuRequestHandler::requests_func_t> MenuRequestHandler::m_requests = {
	{ Codes::LOGOUT, &MenuRequestHandler::_signout },
	{ Codes::GET_ROOM, &MenuRequestHandler::_getRooms },
	{ Codes::GET_PLAYERS_IN_ROOM, &MenuRequestHandler::_getPlayersInRoom },
	{ Codes::STATISTICS, &MenuRequestHandler::_getStatistics },
	{ Codes::JOIN_ROOM, &MenuRequestHandler::_joinRoom },
	{ Codes::CREATE_ROOM, &MenuRequestHandler::_createRoom }
};