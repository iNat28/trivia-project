#pragma once
#include "pch.h"
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "IDatabase.h"
#include "MenuRequestHandler.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory& handlerFactory);

	virtual RequestResult handleRequest(const RequestInfo& requestInfo) const override;
private:
	RequestHandlerFactory& m_handlerFactory;
	using requests_func_t = RequestResult (LoginRequestHandler::*)(const RequestInfo&) const;
	static const map<Codes, LoginRequestHandler::requests_func_t> m_requests;
	
	RequestResult _login(const RequestInfo& requestInfo) const;
	RequestResult _signup(const RequestInfo& requestInfo) const;
};