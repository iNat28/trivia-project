#pragma once
#include "pch.h"
#include "Codes.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"

class IRequestHandler;
class RequestHandlerFactory;
typedef std::shared_ptr<IRequestHandler> IRequestHandlerPtr;

struct RequestInfo
{
	RequestInfo(Codes RequestId, time_t receivalTime, Buffer buffer);
	RequestInfo();

	Codes requestId;
	time_t receivalTime;
	Buffer buffer;
};

struct RequestResult
{
	RequestResult(Buffer response, IRequestHandlerPtr newHandler);
	RequestResult();

	Buffer response;
	IRequestHandlerPtr newHandler;
};

class IRequestHandler
{
public:
	IRequestHandler(RequestHandlerFactory& handlerFactor);

	virtual RequestResult handleRequest(const RequestInfo& requestInfo) const = 0;
protected:
	RequestHandlerFactory& m_handlerFactory;
};