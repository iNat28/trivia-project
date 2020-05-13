#pragma once
#include "pch.h"
#include "IDatabase.h"
#include "LoginManager.h"
#include "IRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabasePtr database);

	LoginRequestHandler createLoginRequestHandler();
	MenuRequestHandler createMenuRequestHandler();
	LoginManager& getLoginManager();
private:
	LoginManager m_loginManager;
	IDatabasePtr m_database;
};

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(IDatabasePtr database);

	virtual bool isRequestRelevant(const RequestInfo& requestInfo) override;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) override;

private:
	RequestHandlerFactory m_handlerFactor;
};

class LoginRequestHandler : public IRequestHandler
{
public:
	//c'tor
	LoginRequestHandler(IDatabasePtr database);

	virtual bool isRequestRelevant(const RequestInfo& requestInfo) override;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) override;

private:
	RequestHandlerFactory m_handlerFactor;

	RequestResult _login(const RequestInfo& requestInfo);
	RequestResult _signup(const RequestInfo& requestInfo);

	//TODO: Add map for request codes and functions
	//using handler_func_t = Buffer(LoginRequestHandler::*)(void);
	//std::unordered_map<RequestCodes, 
};