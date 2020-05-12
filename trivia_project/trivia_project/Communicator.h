
#pragma once
#include "pch.h"
#include "Exception.h"
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

#pragma comment(lib, "Ws2_32.lib")

#define ADDRESS "127.0.0.1"
#define PORT 40200
#define CLIENT_MSG "Hello"
#define CLIENT_BUFFER_MAX 5

class Communicator
{
public:
	Communicator(IDatabasePtr database);

	void startHandleRequests();
private:
	std::unordered_map<SOCKET, IRequestHandlerPtr> m_clients;
	RequestHandlerFactory m_handlerFactory;
	SOCKET m_serverSocket;

	void _bindAndListen();
	static void s_handleNewClient(SOCKET socket, IRequestHandlerPtr handler, std::unordered_map<SOCKET, IRequestHandlerPtr>& client);
	static void s_getFromSocket(SOCKET socket, char* buffer, int length);
	static void s_sendToSocket(SOCKET socket, char* buffer, int length);
};