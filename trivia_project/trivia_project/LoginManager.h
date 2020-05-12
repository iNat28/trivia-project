
#pragma once
#include "pch.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class LoginManager
{
public:
	LoginManager(IDatabasePtr database);

private:
	IDatabasePtr m_database;
};

