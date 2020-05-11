#include "pch.h"
#pragma once
#include "RequestHandlerFactory.h"

class LoginManager
{
	LoginManager(IDatabase& database);
private:
	IDatabase& m_database;
};

