#pragma once
#include "pch.h"
#include "Codes.h"
#include "Requests.h"
#include "JsonResponsePacketSerializer.h"

class IRequestHandler;
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
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) const = 0;
};