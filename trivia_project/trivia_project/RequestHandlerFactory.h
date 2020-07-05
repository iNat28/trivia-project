#pragma once
#include "pch.h"
#include "IDatabase.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "GameRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase& database);
	
	//Maybe allow it so each RequestHandler can use this for one of the parameters, instead of having to get the requestHandler
	//TODO: Look into args, so it'll return std::make_shared<Handler>(*this, args)
	/*template<typename Handler>
	std::shared_ptr<Handler> createRequestHandler(const Handler handler) const
	{
		return std::make_shared<Handler>(handler);
	};*/

	std::shared_ptr<LoginRequestHandler> createLoginRequestHandler();
	std::shared_ptr<MenuRequestHandler> createMenuRequestHandler(LoggedUser user);
	std::shared_ptr<RoomAdminRequestHandler> createRoomAdminRequestHandler(LoggedUser user, Room& room);
	std::shared_ptr<RoomMemberRequestHandler> createRoomMemberRequestHandler(LoggedUser user, Room& room);
	std::shared_ptr<GameRequestHandler> createGameRequestHandler(LoggedUser user);
	
	LoginManager& getLoginManager();
	RoomManager& getRoomManager();
	StatisticsManager& getStatisticsManager();
private:
	IDatabase& m_database;
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	StatisticsManager m_statisticsManager;
};