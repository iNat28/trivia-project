#pragma once
#include "pch.h"
#include "IDatabase.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase& database);
	
	//Maybe allow it so each RequestHandler can use this for one of the parameters, instead of having to get the requestHandler
	//TODO: Look into args, so it'll return std::make_shared<Handler>(*this, args)
	template<typename Handler>
	std::shared_ptr<Handler> createRequestHandler(Handler handler) const
	{
		return std::make_shared<Handler>(handler);
	};
	
	LoginManager& getLoginManager();
	RoomManager& getRoomManager();
	StatisticsManager& getStatisticsManager();
private:
	IDatabase& m_database;
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	StatisticsManager m_statisticsManager;
};