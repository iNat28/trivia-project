#include "pch.h"
#pragma once
#include "LoginRequestHandler.h"

class IDatabase {};

class LoginRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase& database);

	LoginRequestHandler createLoginRequestHandler();
	LoginManager& getLoginManager();
private:
	LoginManager m_loginManager;
	IDatabase& m_database;
};

