#include "pch.h"
#include "Communicator.h"

//Default Constructor
Communicator::Communicator(IDatabasePtr database) : m_handlerFactory(database), m_serverSocket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))
{
	if (this->m_serverSocket == INVALID_SOCKET)
	{
		throw std::exception("Error opening communicator's socket");
	}
}

//Thread for handling new clients
//Input: The client socket
void s_handleNewClient(Communicator& communicator, SOCKET socket, IRequestHandlerPtr handler)
{
	//Recieves from the buffer
	char msgCodeBuffer[MSG_CODE_SIZE + 1] = "";
	char msgLenBuffer[MSG_LEN_SIZE + 1] = "";
	int msgLen = 0;
	RequestInfo requestInfo;
	RequestResult requestResult;
	std::unique_ptr<char[]> msgBuffer;
	char* msgBufferPtr = nullptr;
	std::string username;

	try {
		while (true)
		{
			//Gets from the client the code and the length of the message
			Communicator::s_getFromSocket(socket, msgCodeBuffer, MSG_CODE_SIZE);
			Communicator::s_getFromSocket(socket, msgLenBuffer, MSG_LEN_SIZE);

			//Converts the message length into an int
			memcpy_s(&msgLen, sizeof(int), msgLenBuffer, MSG_LEN_SIZE);

			//Creates the buffer to recieve from the socket
			msgBuffer = std::make_unique<char[]>(size_t(msgLen) + 1);
			msgBufferPtr = msgBuffer.get();
			Communicator::s_getFromSocket(socket, msgBufferPtr, msgLen);

			//Puts the buffers into a RequestInfo
			requestInfo = RequestInfo(
				static_cast<Codes>(msgCodeBuffer[0]),
				std::time(0), //The current time
				Buffer(msgBufferPtr, msgBufferPtr + msgLen)
			);

			//Gets which Request Code it is, and handles it appropriately
			requestResult = handler->handleRequest(requestInfo);
			//handler = requestResult.newHandler;

			//Sends the message
			Communicator::s_sendToSocket(socket, requestResult.response.data(), (int)requestResult.response.size());
		}
	}
	catch (const std::exception & e)
	{
		std::cerr << "From socket " << socket << ": " << e.what() << std::endl;
	}

	//Deal with logout
	//communicator.m_handlerFactory.getLoginManager().logout();
	closesocket(socket);
	communicator.m_clients.erase(socket);
}

//Starts the client handle requests
void Communicator::startHandleRequests()
{
	SOCKET clientSocket = 0;
	std::thread client;

	this->_bindAndListen();

	//Gets the clients and puts them into threads
	while (true)
	{
		//Accepts the client's socket
		clientSocket = accept(this->m_serverSocket, NULL, NULL);
		if (clientSocket == INVALID_SOCKET)
		{
			throw std::exception("Error accepting client");
		}

		IRequestHandlerPtr handler = this->m_handlerFactory.createLoginRequestHandler();

		//Puts the client into a thread
		client = std::thread(s_handleNewClient, std::ref(*this), clientSocket, handler);
		client.detach();

		//Adds the client's socket to the clients
		this->m_clients[clientSocket] = handler;
	}
}

//Binds and listens to the server socket
void Communicator::_bindAndListen()
{
	sockaddr_in sa = { 0 };

	sa.sin_family = AF_INET;
	
	//Adds the address
	inet_pton(AF_INET, ADDRESS, &sa.sin_addr.s_addr);
	//Adds the port
	sa.sin_port = htons(PORT);

	//Binds the socket to the port
	//Connects between the socket and the socket struct
	if (bind(this->m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
	{
		throw std::exception("Error binding socket");
	}

	// Start listening for incoming requests of clients
	if (listen(this->m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		throw std::exception("Error listening to socket");
	}
}


void Communicator::s_getFromSocket(SOCKET socket, char* buffer, int length)
{
	if (INVALID_SOCKET == recv(socket, buffer, length, 0))
	{
		Exception::ex << "Error recieving from socket " << socket;
		throw Exception();
	}
}

void Communicator::s_sendToSocket(SOCKET socket, char* buffer, int length)
{
	if (INVALID_SOCKET == send(socket, buffer, length, 0))
	{
		Exception::ex << "Error sending to socket " << socket;
		throw Exception();
	}
}