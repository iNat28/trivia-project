#include "pch.h"
#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabasePtr database) : 
	m_loginManager(database), m_database(database)
{
}

std::shared_ptr<LoginRequestHandler> RequestHandlerFactory::createLoginRequestHandler()
{
	return std::make_shared<LoginRequestHandler>(*this);
}

std::shared_ptr<MenuRequestHandler> RequestHandlerFactory::createMenuRequestHandler()
{
	return std::make_shared<MenuRequestHandler>(*this);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}