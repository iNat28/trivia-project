#include "pch.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "Server.h"
#include "Communicator.h"
#include "WSAInitializer.h"
#include "json.hpp"

int main()
{
	try
	{
		WSAInitializer wsainitializer;
		Server server;

		server.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}