#include "Server.h"

Server::Server()
{
}

void Server::run()
{
	std::thread t_connector(Server::adminInput);
	t_connector.detach();

	this->m_communicator.startHandleRequests();
}

void Server::adminInput()
{
	std::string input;

	while (input != "EXIT")
	{
		std::cin >> input;
	}

	//Closes the whole program
	std::exit(EXIT_SUCCESS);	//Doesn't do proper clean up
}