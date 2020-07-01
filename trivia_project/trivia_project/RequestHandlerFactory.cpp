#include "pch.h"
#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase& database) : 
	m_loginManager(database), m_database(database), m_statisticsManager(database), m_roomManager(database)
{
}

//std::shared_ptr<LoginRequestHandler> RequestHandlerFactory::createLoginRequestHandler() const
//{
//	return std::make_shared<LoginRequestHandler>(*this);
//}
//
//std::shared_ptr<MenuRequestHandler> RequestHandlerFactory::createMenuRequestHandler(LoggedUser user) const
//{
//	return std::make_shared<MenuRequestHandler>(*this, user);
//}
//
//std::shared_ptr<RoomAdminRequestHandler> RequestHandlerFactory::creatRoomAdminRequestHandler(LoggedUser user, Room room) const
//{
//	return std::make_shared<RoomAdminRequestHandler>(*this, user, room);
//}
//
//std::shared_ptr<RoomMemberRequestHandler> RequestHandlerFactory::creatRoomMemberRequestHandler(LoggedUser user, Room room) const
//{
//	return std::make_shared<RoomMemberRequestHandler>(*this, user, room);
//}

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
