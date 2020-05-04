#pragma once
#include <thread>
#include <iostream>
#include "Communicator.h"

class Server
{
public:
	Server();
	void run();
private:
	Communicator m_communicator;

	static void adminInput();
};

