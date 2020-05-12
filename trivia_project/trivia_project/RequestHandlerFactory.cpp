#include "pch.h"
#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabasePtr database) : 
	m_loginManager(database), m_database(database)
{
}

LoginRequestHandler RequestHandlerFactory::createLoginRequestHandler()
{
	return LoginRequestHandler(this->m_database);
}

MenuRequestHandler RequestHandlerFactory::createMenuRequestHandler()
{
	return MenuRequestHandler(this->m_database);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}
