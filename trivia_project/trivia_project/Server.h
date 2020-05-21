
#pragma once
#include "pch.h"
#include "Communicator.h"
#include "RequestHandlerFactory.h"
#include "SqliteDataBase.h"

class Server
{
public:
	Server();
	void run();

private:
	std::shared_ptr<IDatabase> m_database;
	RequestHandlerFactory m_handlerFactory;
	Communicator m_communicator;

	static void adminInput();
};

