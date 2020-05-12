#include "pch.h"
#pragma once
#include "Constants.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;
interface IRequestHandler;
typedef std::shared_ptr<IRequestHandler> IRequestHandlerPtr;

struct RequestInfo
{
	RequestInfo(RequestCodes RequestId, time_t receivalTime, Buffer buffer);
	RequestInfo();

	RequestCodes requestId;
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

interface IRequestHandler
{
	virtual bool isRequestRelevant(const RequestInfo& requestInfo) = 0;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) = 0;
};