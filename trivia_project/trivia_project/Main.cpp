#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "pch.h"
#include "Server.h"
#include "Communicator.h"
#include "WSAInitializer.h"
#include "json.hpp"


int main()
{
	/*try
	{
		WSAInitializer wsainitializer;
		Server server;

		server.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}*/
	//ErrorResponse errResponse;
	//errResponse.message = "error msg";
	//Buffer buffer = JsonResponsePacketSerializer::serializeResponse(errResponse);
	
	//Buffer buffer = JsonResponsePacketSerializer::serializeResponse(LoginResponse());

	return 0;
}