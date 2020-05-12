#pragma once
#include "pch.h"
#include "IDatabase.h"
#include "MenuRequestHandler.h"
#include "LoginRequestHandler.h"
#include "LoginManager.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabasePtr database);

	LoginRequestHandler createLoginRequestHandler();
	MenuRequestHandler createMenuRequestHandler();
	LoginManager& getLoginManager();
private:
	LoginManager m_loginManager;
	IDatabasePtr m_database;
};