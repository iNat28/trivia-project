#include "pch.h"
#pragma once
#include "Communicator.h"
#include "RequestHandlerFactory.h"
#include "SqliteDataBase.h"

class Server
{
public:
	Server();
	void run();

private:
	IDatabasePtr m_database;
	RequestHandlerFactory m_handlerFactory;
	Communicator m_communicator;

	static void adminInput();
};

