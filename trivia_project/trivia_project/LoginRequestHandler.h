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
	//c'tor
	LoginRequestHandler(RequestHandlerFactory& handlerFactor);

	virtual bool isRequestRelevant(const RequestInfo& requestInfo) override;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) override;
	
	enum class ResponseCodes
	{
		SUCCESFUL,
		USER_DOES_NOT_EXIST,
		USER_ALREADY_IN,
		ERROR_RESPONSE
	};
private:
	RequestHandlerFactory& m_handlerFactor;

	RequestResult _login(const RequestInfo& requestInfo);
	RequestResult _signup(const RequestInfo& requestInfo);

	/*template <typename response>
	RequestResult _loginAll<response>(bool ifSuccess, const response& a);*/
};