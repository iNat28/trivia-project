
#pragma once
#include "pch.h"
#include "LoginRequestHandler.h"
#include "IDatabase.h"
#include "LoginManager.h"
#include "MenuRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;
class LoginManager;
interface IRequestHandler;

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

