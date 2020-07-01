#pragma once
#include "pch.h"
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "IDatabase.h"
#include "MenuRequestHandler.h"

class MenuRequestHandler;

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory& handlerFactor);

	virtual RequestResult handleRequest(const RequestInfo& requestInfo) const override;
private:
	using requests_func_t = RequestResult (LoginRequestHandler::*)(const RequestInfo&) const;
	static const map<Codes, LoginRequestHandler::requests_func_t> m_requests;

	RequestResult _login(const RequestInfo& requestInfo) const;
	RequestResult _signup(const RequestInfo& requestInfo) const;
	std::shared_ptr<MenuRequestHandler> _createMenuRequestHandler(string username) const;
};