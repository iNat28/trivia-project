#include "pch.h"
#pragma once
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class LoginManager
{
public:
	LoginManager(IDatabasePtr database);

private:
	IDatabasePtr m_database;
};

