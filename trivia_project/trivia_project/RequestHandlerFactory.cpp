#include "pch.h"
#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase& database) : 
	loginManager(database), m_database(database)
{
}

LoginRequestHandler RequestHandlerFactory::createLoginRequestHandler()
{
	return LoginRequestHandler(this->m_database);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}
