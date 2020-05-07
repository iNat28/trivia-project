#include "pch.h"
#include "Communicator.h"

//Default Constructor
Communicator::Communicator() : _serverSocket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))
{
	if (this->_serverSocket == INVALID_SOCKET)
	{
		throw std::exception("Error opening communicator's socket");
	}
}

//Deconstructor
Communicator::~Communicator()
{
	for (auto& requestHandlers : m_clients)
	{
		delete requestHandlers.second;
	}
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
		clientSocket = accept(this->_serverSocket, NULL, NULL);
		if (clientSocket == INVALID_SOCKET)
		{
			throw std::exception("Error accepting client");
		}

		//Puts the client into a thread
		client = std::thread(Communicator::s_handleNewClient, clientSocket);
		client.detach();

		//Adds the client's socket to the clients
		this->m_clients[clientSocket] = new LoginRequestHandler();
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
	if (bind(this->_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
	{
		throw std::exception("Error binding socket");
	}

	// Start listening for incoming requests of clients
	if (listen(this->_serverSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		throw std::exception("Error listening to socket");
	}
}

//Thread for handling new clients
//Input: The client socket
void Communicator::s_handleNewClient(SOCKET socket)
{
	//Recieves from the buffer
	char msgCodeBuffer[MSG_CODE_SIZE + 1] = "";
	char msgLenBuffer[MSG_LEN_SIZE + 1] = "";
	char* msgBuffer = nullptr;
	int msgLen = 0;
	LoginRequestHandler loginRequestHandler;
	SignupRequest signupRequest;
	RequestInfo requestInfo;
	Buffer responseBuffer;

	try {
		Communicator::s_getFromSocket(socket, msgCodeBuffer, MSG_CODE_SIZE);
		Communicator::s_getFromSocket(socket, msgLenBuffer, MSG_LEN_SIZE);
		memcpy_s(&msgLen, sizeof(int), msgLenBuffer, MSG_LEN_SIZE);
		msgBuffer = new char[size_t(msgLen + 1)];
		Communicator::s_getFromSocket(socket, msgBuffer, msgLen);

		requestInfo = { static_cast<RequestCodes>(msgCodeBuffer[0]), std::time(0), Buffer(msgBuffer, msgBuffer + msgLen) };

		std::cout << "Buffers: " << msgCodeBuffer << " - " << msgLenBuffer << " - " << msgBuffer << std::endl;

		switch (requestInfo.RequestId)
		{
		case RequestCodes::LOGIN_REQUEST:
			loginRequestHandler.handleRequest(requestInfo);
			responseBuffer = JsonResponsePacketSerializer::serializeResponse(LoginResponse{ 1 });
			break;

		case RequestCodes::SIGNUP_REQUEST:
			signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buffer);
			std::cout << "Username: " << signupRequest.username << " Password: " << signupRequest.password << " Email: " << signupRequest.email << std::endl;
			responseBuffer = JsonResponsePacketSerializer::serializeResponse(SignupResponse{ 1 });
			break;
		}

		//Sends the message
		Communicator::s_sendToSocket(socket, responseBuffer.data(), responseBuffer.size());
	}
	catch (const std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}

	delete[] msgBuffer;
	closesocket(socket);
}

void Communicator::s_getFromSocket(SOCKET socket, char* buffer, size_t length)
{
	if (INVALID_SOCKET == recv(socket, buffer, (int)length, 0))
	{
		Exception::ex << "Error recieving from socket " << socket;
		throw Exception();
	}
}

void Communicator::s_sendToSocket(SOCKET socket, char* buffer, size_t length)
{
	if (INVALID_SOCKET == send(socket, buffer, (int)length, 0))
	{
		Exception::ex << "Error sending to socket " << socket;
		throw Exception();
	}
}
