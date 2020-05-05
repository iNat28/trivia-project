#pragma once
#include <unordered_map>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <thread>
#include "Exception.h"
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"

#pragma comment(lib, "Ws2_32.lib")

#define ADDRESS "127.0.0.1"
#define PORT 40200
#define CLIENT_MSG "Hello"
#define CLIENT_BUFFER_MAX 5

class Communicator
{
public:
	Communicator();

	void startHandleRequests();
private:
	std::unordered_map<SOCKET, IRequestHandler> m_clients;
	SOCKET _serverSocket;

	void _bindAndListen();
	static void _handleNewClient(SOCKET socket);
};