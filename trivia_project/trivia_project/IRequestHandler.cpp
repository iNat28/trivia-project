#include "pch.h"
#include "IRequestHandler.h"

RequestInfo::RequestInfo(RequestCodes RequestId, time_t receivalTime, Buffer buffer) :
	requestId(RequestId), receivalTime(receivalTime), buffer(buffer)
{
}

RequestInfo::RequestInfo() :
	requestId(RequestCodes::ERROR_REQUEST), receivalTime(0)
{
}

RequestResult::RequestResult(Buffer response, IRequestHandlerPtr newHandler) :
	response(response), newHandler(newHandler)
{
}

RequestResult::RequestResult()
{
}