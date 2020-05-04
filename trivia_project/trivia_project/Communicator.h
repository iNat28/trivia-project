#pragma once
#include <unordered_map>
#include <WinSock2.h>
#include <Windows.h>
#include <string>
#include <thread>
#include <iomanip>
#include "Exception.h"
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"

#pragma warning(disable : 4996)
#pragma comment(lib, "Ws2_32.lib")

#define ADDRESS "127.0.0.1"
#define PORT 40200

class Communicator
{
public:
	Communicator();

	void startHandleRequests();
private:
	std::unordered_map<SOCKET, IRequestHandler> m_clients;
	SOCKET _socket;

	void _bindAndListen();
	static void _handleNewClient();
};