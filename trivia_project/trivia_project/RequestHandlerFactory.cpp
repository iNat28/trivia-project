#include "pch.h"
#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase& database) : 
	m_loginManager(database), m_database(database), m_statisticsManager(database), m_roomManager(database), m_gameManager(database)
{
}

LoginRequestHandler& RequestHandlerFactory::createLoginRequestHandler()
{
	static LoginRequestHandler loginRequestHandler(*this);
	return loginRequestHandler;
}

MenuRequestHandler& RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
	static MenuRequestHandler menuRequestHandler(*this);
	menuRequestHandler.reset(user);
	return menuRequestHandler;
}

RoomAdminRequestHandler& RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser user, Room& room)
{
	static RoomAdminRequestHandler roomAdminRequestHandler(*this);
	roomAdminRequestHandler.reset(user, room);
	return roomAdminRequestHandler;
}

RoomMemberRequestHandler& RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser user, Room& room)
{
	static RoomMemberRequestHandler roomMemberRequestHandler(*this);
	roomMemberRequestHandler.reset(user, room);
	return roomMemberRequestHandler;
}

GameRequestHandler& RequestHandlerFactory::createGameRequestHandler(LoggedUser user, Game& game)
{
	static GameRequestHandler gameRequestHandler(*this);
	gameRequestHandler.reset(user, game);
	return gameRequestHandler;
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	return this->m_roomManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return this->m_statisticsManager;
}

GameManager& RequestHandlerFactory::getGameManager()
{
	return this->m_gameManager;
}
