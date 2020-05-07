#include "pch.h"
#pragma once
#include "Exception.h"
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

#pragma comment(lib, "Ws2_32.lib")

#define ADDRESS "127.0.0.1"
#define PORT 40200
#define CLIENT_MSG "Hello"
#define CLIENT_BUFFER_MAX 5

class Communicator
{
public:
	Communicator();
	~Communicator();

	void startHandleRequests();
private:
	std::unordered_map<SOCKET, IRequestHandler*> m_clients;
	SOCKET _serverSocket;

	void _bindAndListen();
	static void s_handleNewClient(SOCKET socket);
	static void s_getFromSocket(SOCKET socket, char* buffer, unsigned int length);
	static void s_sendToSocket(SOCKET socket, char* buffer, unsigned int length);
};