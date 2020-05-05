#include "Communicator.h"

Communicator::Communicator() : _socket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))
{
	if (this->_socket == INVALID_SOCKET)
	{
		throw std::exception("Error opening communicator's socket");
	}
}

void Communicator::startHandleRequests()
{
	SOCKET clientSocket = 0;
	std::thread client;

	this->_bindAndListen();

	//Gets the clients and puts them into threads
	while (true)
	{
		//Accepts the client's socket
		clientSocket = accept(this->_socket, NULL, NULL);
		if (clientSocket == INVALID_SOCKET)
		{
			throw std::exception("Error accepting client");
		}

		//Puts the client into a thread
		client = std::thread(Communicator::_handleNewClient, clientSocket);
		client.detach();

		//Adds the client's socket to the clients
		this->m_clients[clientSocket] = LoginRequestHandler();
	}
}

void Communicator::_bindAndListen()
{
	struct sockaddr_in sa = { 0 };

	sa.sin_family = AF_INET;
	//Adds the address

	inet_pton(AF_INET, ADDRESS, &sa.sin_addr.s_addr);
	//Adds the port
	sa.sin_port = htons(PORT);

	//Binds the socket to the port
	//Connects between the socket and the socket struct
	if (bind(this->_socket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
	{
		throw std::exception("Error binding socket");
	}

	// Start listening for incoming requests of clients
	if (listen(this->_socket, SOMAXCONN) == SOCKET_ERROR)
	{
		throw std::exception("Error listening to socket");
	}
}

void Communicator::_handleNewClient(SOCKET socket)
{
	//Recieves from the buffer
	char buffer[CLIENT_BUFFER_MAX + 1] = "";

	if (INVALID_SOCKET == send(socket, CLIENT_MSG, strlen(CLIENT_MSG), 0))
	{
		Exception::ex << "Error sending to socket " << socket;
		throw Exception();
	}

	if (INVALID_SOCKET == recv(socket, buffer, sizeof(char) * CLIENT_BUFFER_MAX, 0))
	{
		Exception::ex << "Error recieving from socket " << socket;
		throw Exception();
	}

	if (CLIENT_MSG == std::string(buffer))
	{
		std::cout << CLIENT_MSG << std::endl;
	}

	closesocket(socket);
}