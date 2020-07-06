#include "pch.h"
#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase& database) : 
	m_loginManager(database), m_database(database), m_statisticsManager(database), m_roomManager(database), m_gameManager(database)
{
}

std::shared_ptr<LoginRequestHandler> RequestHandlerFactory::createLoginRequestHandler()
{
	return std::make_shared<LoginRequestHandler>(*this);
}

std::shared_ptr<MenuRequestHandler> RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
	return std::make_shared<MenuRequestHandler>(*this, user);
}

std::shared_ptr<RoomAdminRequestHandler> RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser user, Room& room)
{
	return std::make_shared<RoomAdminRequestHandler>(*this, user, room);
}

std::shared_ptr<RoomMemberRequestHandler> RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser user, Room& room)
{
	return std::make_shared<RoomMemberRequestHandler>(*this, user, room);
}

std::shared_ptr<GameRequestHandler> RequestHandlerFactory::createGameRequestHandler(LoggedUser user, Game& game)
{
	return std::make_shared<GameRequestHandler>(*this, user, game);
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
