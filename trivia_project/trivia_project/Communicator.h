#include "pch.h"
#pragma once
#include "Exception.h"
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"

#pragma comment(lib, "Ws2_32.lib")

#define ADDRESS "127.0.0.1"
#define PORT 40200
#define CLIENT_MSG "Hello"
#define CLIENT_BUFFER_MAX 5

class Communicator
{
public:
	Communicator(RequestHandlerFactory& handlerFactory);

	void startHandleRequests();
private:
	std::unordered_map<SOCKET, std::shared_ptr<IRequestHandler>> m_clients;
	RequestHandlerFactory& m_handlerFactory;
	SOCKET m_serverSocket;

	void _bindAndListen();
	static void s_handleNewClient(SOCKET socket, std::shared_ptr<IRequestHandler> handler, std::unordered_map<SOCKET, IRequestHandler>& client);
	static void s_getFromSocket(SOCKET socket, char* buffer, int length);
	static void s_sendToSocket(SOCKET socket, char* buffer, int length);
};