#include "pch.h"
#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase& database) : 
	m_loginManager(database), m_database(database), m_statisticsManager(database)
{
}

std::shared_ptr<LoginRequestHandler> RequestHandlerFactory::createLoginRequestHandler()
{
	return std::make_shared<LoginRequestHandler>(*this);
}

std::shared_ptr<MenuRequestHandler> RequestHandlerFactory::createMenuRequestHandler()
{
	return std::make_shared<MenuRequestHandler>(*this);
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
