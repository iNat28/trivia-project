#pragma once
#include "pch.h"
#include "IDatabase.h"
#include "LoginManager.h"
#include "IRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase& database);

	std::shared_ptr<LoginRequestHandler> createLoginRequestHandler();
	std::shared_ptr<MenuRequestHandler> createMenuRequestHandler();
	LoginManager& getLoginManager();
private:
	LoginManager m_loginManager;
	IDatabase& m_database;
};