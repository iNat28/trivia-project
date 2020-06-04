#include "pch.h"
#include "MenuRequestHandler.h"

//TODO: Make sure things are const

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactor) :
	m_handlerFactor(handlerFactor), m_user("") //TODO: CHANGE
{
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& requestInfo) const
{
	RequestResult requestResult;

	//TODO: Move this and Login Request Handler switch cases to Map of codes and functions

	//If at any point the login or sign up doesn't work, an exception will be thrown, 
	//and it will be put into an error response
	try {
		switch (requestInfo.requestId)
		{
		case Codes::LOGOUT:
			requestResult = this->_signout(requestInfo);
			break;
		case Codes::GET_ROOM:
			requestResult = this->_getRooms(requestInfo);
			break;
		case Codes::GET_PLAYERS_IN_ROOM:
			requestResult = this->_getPlayersInRoom(requestInfo);
			break;
		case Codes::STATISTICS:
			requestResult = this->_getStatistics(requestInfo);
			break;
		case Codes::JOIN_ROOM:
			requestResult = this->_joinRoom(requestInfo);
			break;
		case Codes::CREATE_ROOM:
			requestResult = this->_createRoom(requestInfo);
			break;
		default:
			throw Exception("Request Code not valid");
		}
	}
	//Manager exception caught
	catch (const Exception & e)
	{
		requestResult = RequestResult(
			JsonResponsePacketSerializer::serializeResponse(ErrorResponse(e.what())),
			m_handlerFactor.createLoginRequestHandler());
	}
	//Other exception caught (probably because of the json)
	catch (...)
	{
		requestResult = RequestResult(
			JsonResponsePacketSerializer::serializeResponse(ErrorResponse("Unkown error occured")),
			nullptr);
	}

	return requestResult;
}

RequestResult MenuRequestHandler::_signout(const RequestInfo& requestInfo) const
{
	//TODO: Create a struct for LogoutRequest
	string logoutRequestUsername = json::from_bson(requestInfo.buffer)[Keys::username];

	//Throws an Exception if the login doesn't work
	this->m_handlerFactor.getLoginManager().logout(logoutRequestUsername);

	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(LogoutResponse(static_cast<unsigned int>(ResponseCodes::SUCCESFUL))),
		m_handlerFactor.createMenuRequestHandler());
}

RequestResult MenuRequestHandler::_getRooms(const RequestInfo& requestInfo) const
{
	//Throws an Exception if the login doesn't work
	vector<Room> rooms = this->m_handlerFactor.getRoomManager().getRooms();

	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(GetRoomResponse(static_cast<unsigned int>(ResponseCodes::SUCCESFUL), rooms)),
		m_handlerFactor.createMenuRequestHandler());
}

RequestResult MenuRequestHandler::_getPlayersInRoom(const RequestInfo& requestInfo) const
{
	RoomIdRequest getPlayersInRoomRequest = JsonRequestPacketDeserializer::deserializeRoomIdRequest(requestInfo.buffer);
	vector<Room> rooms = this->m_handlerFactor.getRoomManager().getRooms();

	//TODO: Move to a new function in Room Manager
	for (const auto& room : rooms)
	{
		if (room.getRoomData().id == getPlayersInRoomRequest.roomId)
		{
			return RequestResult(
				JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse(room.getAllUsers())),
				m_handlerFactor.createMenuRequestHandler());
		}
	}
	
	//TODO: Make sure other functions in Room Manager throw exceptions
	throw Exception("Room ID not found");
}

//TODO: Create the rest

RequestResult MenuRequestHandler::_getStatistics(const RequestInfo& requestInfo) const
{
	return RequestResult();
}

RequestResult MenuRequestHandler::_joinRoom(const RequestInfo& requestInfo) const
{
	return RequestResult();
}

RequestResult MenuRequestHandler::_createRoom(const RequestInfo& requestInfo) const
{
	return RequestResult();
}
